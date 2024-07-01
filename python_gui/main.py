
from tkinter import *
from tkinter.ttk import *

from subprocess import Popen, PIPE, STDOUT

window = Tk()
window.title("Fluid Simulator Constants")
window.geometry("200x800-20+0")

paused = True
pause_text= StringVar(value="resume")
grid_value = StringVar(value="0")
particle_value = StringVar(value="1")
contour_value = StringVar(value="1")

gravity_value = StringVar(value="1")
gravity_scalar = StringVar(value="1")

fluid_value = StringVar(value="1")
pressure_value = StringVar(value="20")
smoothing_value = StringVar(value="15")

check_button = {
        "onvalue": "1",
        "offvalue": "0"
}

def update(var, value):
    p.stdin.write(f"{var} {value}\n".encode())
    p.stdin.flush()

def close_simulator():
    update("q", 1)

def on_pause():
    global pause_text, paused
    if not paused:
        pause_text.set("resume")
    else:
        pause_text.set("STOP")

    paused = not paused
    update('!', int(paused))


def on_grid():
        global grid_value
        update("g", grid_value.get())
def on_particles():
        global particle_value
        update("p", particle_value.get())
def on_contour():
    global contour_value
    update("c", contour_value.get())
def on_gravity():
    global gravity_value
    update("G", gravity_value)
def on_gravity_f(e):
    global gravity_scalar;
    update("G",gravity_scalar.get())

def on_fluid(e):
        global fluid_value
        update("f", fluid_value.get())
def on_pressure(e):
        global pressure_value
        update("k", pressure_value.get())
def on_smoothing(e):
    global smoothin_value
    update("h", smoothing_value.get())

pause_btn = Button(textvariable=pause_text, command=on_pause);

draw_grid = Checkbutton(text="Display Grid", command=on_grid, variable=grid_value, **check_button)
draw_particles = Checkbutton(text="Show Particles", command=on_particles, variable=particle_value, **check_button)
draw_contour = Checkbutton(text="Draw Contour", command=on_contour, variable=contour_value, **check_button)

gravity = Checkbutton(text="Enable Gravity", command=on_gravity, variable=gravity_value, **check_button)

fluid_density = Scale(from_=0.1, to=2, command=on_fluid, variable=fluid_value)
pressure_multiplier = Scale(from_=0.1, to=30, command=on_pressure, variable=pressure_value)
smoothing_radius = Scale(from_=1, to=20, command=on_smoothing, variable=smoothing_value)
gravity_force = Scale(from_=0.1, to=10, command=on_gravity_f, variable=gravity_scalar)

label1 = Label(text="Fluid Density")
label12 = Label(textvariable=fluid_value)
label2 = Label(text="Pressure Multiplier")
label22 = Label(textvariable=pressure_value)
label3 = Label(text="Smoothin Radius")
label32 = Label(textvariable=smoothing_value)
label4 = Label(text="Gravity Scalar")
label42 = Label(textvariable=gravity_scalar)


widgets = [pause_btn, draw_grid, draw_particles, draw_contour, gravity, label1, fluid_density, label12, label2, pressure_multiplier, label22, label3, smoothing_radius, label32, label4, gravity_force, label42]

for w in widgets:
    w.pack()

p = Popen(['../fluid-simulator'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

window.mainloop()

close_simulator()
p.terminate()
