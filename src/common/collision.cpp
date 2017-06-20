#include "collision.h"

Collision::Collision()
    : dist(1e9)
{
}

void Collision::collide(){
  dist = 1e9+1;
}

void Collision::setCollision(Collision* coll)
{
  coll->dist = 1e9+1;
}

void Collision::setCollision(Collision* coll,const Vector3& start,
   const Vector3& dir, double t, const Vector3& n, 
   const Object* obj, bool in)
{
  coll->object = obj;
  coll->light = nullptr;
  coll->ray_start = start;
  coll->ray_dir = dir.unitize();
  coll->p = start + dir * t;
  coll->n = n;
  coll->dist = t * dir.mod();
  coll->is_internal = in;
}

void Collision::collide(const Vector3& start, const Vector3& dir, double t,
                     const Vector3& n, const Object* obj, bool in)
{
  if(DEBUG==1)printf("a\n");
  this->object = obj;
  this->light = nullptr;
  this->ray_start = start;
  this->ray_dir = dir.unitize();
  this->p = start + dir * t;
  this->n = n;
  this->dist = t * dir.mod();
  this->is_internal = in;
}

void Collision::setCollision(Collision* coll,const Vector3& start,
  const Vector3& dir, double t, double u, double v,
  const Vector3& n, const Object* obj, bool in)
{
  coll->object = obj;
  coll->light = nullptr;
  coll->ray_start = start;
  coll->ray_dir = dir.unitize();
  coll->p = start + dir * t;
  coll->n = n;
  coll->dist = t * dir.mod();
  coll->is_internal = in;
}

void Collision::collide(const Vector3& start, const Vector3& dir, 
  double t, double u, double v,
  const Vector3& n, const Object* obj, bool in)
{
  if(DEBUG==1)printf("b\n");
  this->object = obj;
  this->light = nullptr;
  this->ray_start = start;
  this->ray_dir = dir.unitize();
  this->p = start + dir * t;
  this->n = n;
  this->u = u; this->v = v;
  this->dist = t * dir.mod();
  this->is_internal = in;
}

void Collision::setCollision(Collision* coll,const Vector3& start,
  const Vector3& dir, double t, const Light* l)
{
  coll->object = nullptr;
  coll->light = l;
  coll->ray_start = start;
  coll->ray_dir = dir.unitize();
  coll->p = start + dir * t;
  coll->is_internal = false;
}

void Collision::collide(const Vector3& start, const Vector3& dir,
  double t, const Light* l)
{
  if(DEBUG==1)printf("c\n");
  this->object = nullptr;
  this->light = l;
  this->ray_start = start;
  this->ray_dir = dir.unitize();
  this->p = start + dir * t;
  this->is_internal = false;
}
