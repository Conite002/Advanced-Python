import random
def monte_carlo_pi(nsamples):
    pi = 0.
    circle_points = 0
    square_points = 0
    interval = 0
    for _ in range(nsamples):
        x = random.random()
        y = random.random()
        d = x*x + y*y

        if d <= 1 :
            circle_points = circle_points + 1
        square_points = square_points + 1 
        interval = interval + 1

    pi = 4 * (circle_points / square_points)
    print(f"Estimated pi: {pi}")
    return pi