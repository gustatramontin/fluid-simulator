
from tkinter import *
from tkinter.ttk import *

from subprocess import Popen, PIPE, STDOUT

window = Tk()
window.title("Fluid Simulator Constants")
window.geometry("200x800-20+0")

grid_value = StringVar(value="0")
particle_value = StringVar(value="1")
contour_value = StringVar(value="1")

fluid_value = StringVar(value="1")
pressure_value = StringVar(value="25.1")
smoothing_value = StringVar(value="10")

check_button = {
        "onvalue": "1",
        "offvalue": "0"
}

def update(var, value):
    p.stdin.write(f"{var} {value}\n".encode())
    p.stdin.flush()


def on_grid():
        global grid_value
        update("g", grid_value.get())
def on_particles():
        global particle_value
        update("p", particle_value.get())
def on_contour():
    global contour_value
    update("c", contour_value.get())

def on_fluid(e):
        global fluid_value
        update("f", fluid_value.get())
def on_pressure(e):
        global pressure_value
        update("k", pressure_value.get())
def on_smoothing(e):
    global smoothin_value
    update("h", smoothing_value.get())

draw_grid = Checkbutton(text="Display Grid", command=on_grid, variable=grid_value, **check_button)
draw_particles = Checkbutton(text="Show Particles", command=on_particles, variable=particle_value, **check_button)
draw_contour = Checkbutton(text="Draw Contour", command=on_contour, variable=contour_value, **check_button)



fluid_density = Scale(from_=0.1, to=2, command=on_fluid, variable=fluid_value)
pressure_multiplier = Scale(from_=0.1, to=30, command=on_pressure, variable=pressure_value)
smoothing_radius = Scale(from_=1, to=20, command=on_smoothing, variable=smoothing_value)

label1 = Label(text="Fluid Density")
label12 = Label(textvariable=fluid_value)
label2 = Label(text="Pressure Multiplier")
label22 = Label(textvariable=pressure_value)
label3 = Label(text="Smoothin Radius")
label32 = Label(textvariable=smoothing_value)


widgets = [draw_grid, draw_particles, draw_contour, label1, fluid_density, label12, label2, pressure_multiplier, label22, label3, smoothing_radius, label32]

for w in widgets:
    w.pack()

p = Popen(['../fluid-simulator'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

window.mainloop()
