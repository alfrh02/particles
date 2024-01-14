# 2D Particle System

There is only one particle class, `Particle`, which defines all default particle behaviour.

The `Particle` class takes in a function pointer. This function has one parameter, which is the reference of a Particle. `Particle` will call this function using `*this`.

This means that unique behaviour can be defined without having to define a whole new class. `particleConfig.hpp` contains all of the different particle types. Each particle type is a struct that contains variables such as colour, size, lifespan, and more.

New particle types can be easily deployed by anybody with some rudimentary programming knowledge, as they can copy the syntax used in other particle structs.

### Todo

~~- [ ] More Particle parameters to be passed into Emitter - including being inputted as ranges~~
    ~~- [ ] Color~~
    ~~- [ ] Size~~
    ~~- [ ] Velocity~~
- [x] Particle types
    - [x] Smoke
    - [x] Electricity
    - [x] Fire
    - [x] Rain
    - [x] Bubbles
- [x] 2D objects for particles to interact with
    - [ ] Objects that are:
        - [x] Placeable
        - [ ] Rotatable
    - [x] Collision detection
- [x] Additional Emitter behaviour
    - [x] GUI Elements
    - [x] Spawn area
        - [x] Emitter turns into a rectangle, where user can specify width/height, Particle objects will spawn randomly within that rectangle