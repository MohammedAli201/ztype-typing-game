# Aimed shots and collision

The original group project calculates a direction vector in `Bullet::UnitVector` (`src/ZType/bullet.cpp`) by subtracting the bullet and target positions and dividing by the vector length. Its movement subtracts that direction; its collision check compares vertical positions. The browser version reimplements this idea with explicit time-based motion, homing, and distance-based collision. It does not claim to be an exact port of the original physics.

For projectile position **p** and its assigned target position **q**:

```
d = q - p
distance = hypot(d.x, d.y)
direction = d / distance
velocity = direction * speed
p += direction * min(speed * deltaTime, distance - hitRadius)
```

The engine checks `distance <= hitRadius` before normalization to avoid dividing by zero. Travel is clamped so a shot cannot tunnel through its target during a slow frame. Each update recalculates the unit vector toward that shot's target ID, allowing the projectile to follow a moving word even after the player starts typing another target. This is arcade kinematics, not a gravity or rigid-body simulation.

The simulation uses an 800 × 400 world and an SVG layer that maps to the arena. Speed is 850 world units per active second, and the hit radius is 12 units. The ship aims with `atan2(dy, dx)`. Expanding impact rings and radial particles appear at the collision point, then expire. Pausing freezes motion and effects; restarting creates a new game state. Reduced-motion users see stationary impact indicators without laser travel, expanding rings, sparks, or ship rotation; the underlying collision rules are unchanged.

Each accepted letter creates one shot. Incorrect letters do not fire. Correct letters and fully typed words retain the existing immediate score rewards. A fully typed word is secured against shield loss, remains visible, and disappears only when all its shots hit. Focus waits for that impact before presenting its next word, ignoring keys during this short gap. If an unfinished word escapes, its shots are discarded. Session results count typing completed before the timer ends, even if the final visual shot was still travelling.

`tests/physics.test.mjs` covers unit vectors, moving targets, frame-rate-independent travel to a fixed target, overshoot, coincident positions, firing rules, target identity, delayed destruction, pause, cancellation, and effect cleanup.
