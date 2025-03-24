#pragma once
#include <vector>
#include <list>
#include "external/glm/vec4.hpp"
#include "external/glm/vec2.hpp"
#include "general/inc/drawable.h"
#include "resources/pub/tx_textures.h"

class Unit : public IDrawable
{
public:
								Unit();

	virtual bool				CheckCollision(Unit& _other) = 0;

	void						SetPosition(glm::vec2 _pos);
	void						SetPosition(float _x, float _y);
	void						SetSize(float _size);
	void						SetColor(glm::vec4 _col);
	void						SetColor(float _r, float _g, float _b, float _a = 1.0f);

	glm::vec2					GetPosition();
	float						GetSize();
	glm::vec4					GetColor();
protected:
private:
	float						m_size;
	glm::vec2					m_position;
	glm::vec4					m_color;
};

class Box : public Unit
{
public:
	bool						CheckCollision(Unit& _other) override;
	void						Draw(Resources& _resources) override;
private:
};

class Enemy;

class Movement
{
public:
	enum Type
	{
		Undefined = -1,
		Linear,
		ZigZag,
		Spiral,

		__count
	};

								Movement();

	void						Create(Type _type, float _speed);
	void						Process(Enemy& _enemy, const float& _dt);
private:
	float						m_speed;
	float						m_angle;
	Type						m_type;
};

class Enemy : public Unit
{
public:

	bool						CheckCollision(Unit& _other) override;
	void						Draw(Resources& _resources) override;

	void						Move(glm::vec2 _offset);
	void						CreateMovement(Movement::Type _type, float _speed);
	void						MovementProcess(const float& _dt);
private:
	Movement					m_movement;
};

class EnemySpawner
{
public:
								EnemySpawner();
								~EnemySpawner();

	void						Prepare();
	void						MovementProcess(const float& _dt);

	Enemy*						Create(const float& _dt);
	void						Remove(Enemy* _enemy);
	std::list<Enemy*>&			GetList();
private:
	int							m_counter;
	float						m_timeline;
	float						m_move_speed;
	float						m_spawn_speed;
	std::list<Enemy*>			m_enemy_list;
	std::vector<Enemy*>			m_pending_list;
};

class Player : public Unit
{
public:
	bool						CheckCollision(Unit& _other) override;
	void						Draw(Resources& _resources) override;

	void						SetBoxPosition(glm::vec2 _pos);
	void						SetBoxPosition(float _x, float _y);
	void						SetBoxSize(float _size);
	void						SetBoxColor(glm::vec4 _col);
	void						SetBoxColor(float _r, float _g, float _b, float _a = 1.0f);

	void						Move(float _offset);
private:
	Box							m_box;
};