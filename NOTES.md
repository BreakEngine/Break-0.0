# Notes and TODOs

## TODOs ##
  - Saad: make a custom renderer for 2D rendering or maybe a batcher to render 2D

## Notes ##
  - Saad: when rendering 2D we need a set of settings, it's not feasible to turn
          settings on then off every time we need to render 2D objects, a better
          alternative is to centralize 2D rendering and we may try to optimize
          it further: - A batcher with a single geometry that holds all 2D data
                        and renders it in one draw call per batch.

          Q: is it better to use instancing for constant geometries, such as quads,
          circles, ...etc.?

          say we want to draw 1000 quad, with this layout [vec2:POSITION, vec4:COLOR]
          this will cost 8 + 16 = 24 byte per vertex, 1000 * 24 = 240000 byte which is
          roughly 24 mgb, but say now we want to draw 10000 quad, that will cost 240 mgb
          which is not a good to waste all this memory.

          instancing offers a better alternative for this case we use the same geometry which
          is 24 byte, one disadvantage for instancing is we will face the same memory waste if
          shader uses uniforms, but for simple geometries like rectangle or circle we'll not want
          to use uniforms at all i think, but wait ... since we'll use the same geometry we should make
          an offset array as uniform, let's say we'll use the 10000 rectangle again, vec2 8 * 10000 =
          80000 byte, which is roughly 80 mgb, that's better than pervious method.

          we may use the second method since it costs less memory, and organize rendering in batches of 1000
          unit, this way we can make use of optimal dynamic buffer size.

          Final: for sprite sheets we will use same method as rectangles with a sorted batches based on
          texture use to minimize state changes

