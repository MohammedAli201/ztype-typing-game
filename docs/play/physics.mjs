// A fixed 800 × 400 world keeps physics independent of CSS and screen size.
export const SHIP = { x: 400, y: 368 };
export function targetPosition(target, mode) {
  return mode === 'focus' ? { x: 400, y: 192 } : { x: 80 + target.lane * 160, y: 64 + target.y * 272 };
}

// Recompute the unit vector each step: a shot follows its own moving target.
// Clamp travel at the collision radius so fast frames cannot overshoot.
export function advanceShot(shot, destination, dt, speed = 850, radius = 12) {
  const dx = destination.x - shot.x, dy = destination.y - shot.y;
  const distance = Math.hypot(dx, dy);
  if (distance <= radius) return true;
  if (!Number.isFinite(dt) || dt <= 0) return false;
  const travel = Math.min(speed * dt, distance - radius);
  shot.vx = dx / distance * speed; shot.vy = dy / distance * speed;
  shot.x += dx / distance * travel; shot.y += dy / distance * travel;
  return distance - travel <= radius + 1e-8;
}
