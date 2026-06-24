import random
import pygame

WIDTH, HEIGHT = 800, 600
FPS = 60
PADDLE_WIDTH, PADDLE_HEIGHT = 12, 110
BALL_SIZE = 18
PADDLE_SPEED = 7
BALL_SPEED = 7

WHITE = (245, 245, 245)
BLUE = (50, 170, 255)
DARK = (18, 24, 42)
GREEN = (40, 220, 120)


class Paddle:
    def __init__(self, x, y):
        self.rect = pygame.Rect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT)

    def move(self, dy):
        self.rect.y += dy * PADDLE_SPEED
        self.rect.y = max(0, min(HEIGHT - PADDLE_HEIGHT, self.rect.y))

    def draw(self, surface):
        pygame.draw.rect(surface, BLUE, self.rect, border_radius=6)

    def ai_move(self, ball):
        if ball.rect.centery > self.rect.centery + 10:
            self.move(1)
        elif ball.rect.centery < self.rect.centery - 10:
            self.move(-1)


class Ball:
    def __init__(self):
        self.rect = pygame.Rect(0, 0, BALL_SIZE, BALL_SIZE)
        self.reset()

    def reset(self, direction=None):
        self.rect.center = (WIDTH // 2, HEIGHT // 2)
        dx = direction if direction is not None else random.choice([-1, 1])
        dy = random.choice([-1, 1])
        self.velocity = [dx * BALL_SPEED, dy * BALL_SPEED]

    def update(self, left_paddle, right_paddle):
        self.rect.x += self.velocity[0]
        self.rect.y += self.velocity[1]

        if self.rect.top <= 0 or self.rect.bottom >= HEIGHT:
            self.velocity[1] *= -1

        if self.rect.colliderect(left_paddle.rect) and self.velocity[0] < 0:
            self.velocity[0] *= -1
            self.velocity[1] += (self.rect.centery - left_paddle.rect.centery) * 0.05

        if self.rect.colliderect(right_paddle.rect) and self.velocity[0] > 0:
            self.velocity[0] *= -1
            self.velocity[1] += (self.rect.centery - right_paddle.rect.centery) * 0.05

    def draw(self, surface):
        pygame.draw.ellipse(surface, GREEN, self.rect)


def draw_text(surface, text, size, x, y, color=WHITE):
    font = pygame.font.Font(None, size)
    rendered = font.render(text, True, color)
    surface.blit(rendered, (x, y))


def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Paddle Rush")
    clock = pygame.time.Clock()

    left_paddle = Paddle(24, HEIGHT // 2 - PADDLE_HEIGHT // 2)
    right_paddle = Paddle(WIDTH - 24 - PADDLE_WIDTH, HEIGHT // 2 - PADDLE_HEIGHT // 2)
    ball = Ball()

    left_score = 0
    right_score = 0
    running = True
    playing = False

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_SPACE:
                    playing = not playing
                    if not playing:
                        ball.reset()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_w]:
            left_paddle.move(-1)
        if keys[pygame.K_s]:
            left_paddle.move(1)

        if playing:
            right_paddle.ai_move(ball)
            ball.update(left_paddle, right_paddle)

            if ball.rect.left <= 0:
                right_score += 1
                ball.reset(direction=1)
            elif ball.rect.right >= WIDTH:
                left_score += 1
                ball.reset(direction=-1)

        screen.fill(DARK)
        pygame.draw.line(screen, WHITE, (WIDTH // 2, 0), (WIDTH // 2, HEIGHT), 2)
        left_paddle.draw(screen)
        right_paddle.draw(screen)
        ball.draw(screen)

        draw_text(screen, f"Player: {left_score}", 34, 30, 15)
        draw_text(screen, f"CPU: {right_score}", 34, WIDTH - 170, 15)

        if not playing:
            draw_text(screen, "Press SPACE to start", 42, WIDTH // 2 - 180, HEIGHT // 2 - 40)
            draw_text(screen, "W/S to move", 28, WIDTH // 2 - 100, HEIGHT // 2 + 18)

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()


if __name__ == "__main__":
    main()
