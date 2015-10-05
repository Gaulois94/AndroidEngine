#include "Effect.h"

Effect::Effect(Updatable* parent, ExplosionMaterial* material) : Drawable(parent, material), m_particles(NULL)
{}
