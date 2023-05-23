import turtle

def draw_fractal(sequence, length, angle):
  t = turtle.Turtle()
  screen = turtle.Screen()
  stack = []

  for move in sequence:
    if move == 'F':
      t.forward(length)
    elif move == '+':
      t.right(angle)
    elif move == '-':
      t.left(angle)
    elif move == '[':
      stack.append((t.heading(), t.position()))
    elif move == ']':
      heading, position = stack.pop()
      t.penup()
      t.setheading(heading)
      t.goto(position)
      t.pendown()

  screen.exitonclick()


sequence = "F+F+F+F" #cola sua sequencia de F's aqui
draw_fractal(sequence, 10, 90) #string, tamanho do traço e angulo de mudança
#recomendo usar o replit python com turtle, é um tipo especifico
