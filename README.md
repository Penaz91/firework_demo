Fireworks Demo
-----------------

Small Demo I made for a friend that displays a star field with 1000 stars, all generated with circles.

Clicking somewhere on the window will shoot a firework on that place, using ease-out functions.

When the firework explodes, particles will be emitted to match a certain shape.

Patterns
---------

Shapes can be edited and added in the `resources/patterns` directory.

Each black pixel represents a random color particle. Transparent pixels won't create particles. Colored pixels will have their color taken and used to create the particles.

Building the project
---------------------

You will need the latest version of SFML and a compiler that supports C++17's `<filesystem>`.

The project includes a makefile that allows to build the project by just using the `make` command.
