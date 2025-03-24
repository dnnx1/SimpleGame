#include <random>
#include "external/GL/glew.h"
#include "external/GLFW/glfw3.h"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "units/inc/unit.h"
#include "utility/inc/draw.h"

Unit::Unit()
	: m_size(0.0f)
	, m_position(0.0f, 0.0f)
	, m_color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

void Unit::SetPosition(glm::vec2 _pos)
{
	m_position = _pos;
}

void Unit::SetPosition(float _x, float _y)
{
	SetPosition({ _x, _y });
}

void Unit::SetSize(float _size)
{
	m_size = _size;
}

void Unit::SetColor(glm::vec4 _col)
{
	m_color = _col;
}

void Unit::SetColor(float _r, float _g, float _b, float _a)
{
	SetColor({ _r, _g, _b, _a });
}

glm::vec2 Unit::GetPosition()
{
	return m_position;
}

float Unit::GetSize()
{
	return m_size;
}

glm::vec4 Unit::GetColor()
{
	return m_color;
}

bool Box::CheckCollision(Unit& _other)
{
	return (glm::distance(GetPosition(), _other.GetPosition())) < (GetSize() / 2.0f + _other.GetSize() / 2.0f);
}

void Box::Draw(Resources& _resources)
{
	glm::vec2 size(GetSize());
	draw::Sprite(_resources, tx::Box, GetPosition() + size / 2.0f, size, GetColor());
}


Movement::Movement()
	: m_speed(0.0f)
	, m_angle(0.0f)
	, m_type(Undefined)
{
}

void Movement::Create(Type _type, float _speed)
{
	m_type = _type;
	m_speed = _speed;
}

void Movement::Process(Enemy& _enemy, const float& _dt)
{
	switch (m_type)
	{
	case Movement::Linear:
		_enemy.Move({ 0.0f, m_speed * _dt });
		break;

	case Movement::ZigZag:
		m_angle += 3.1415f * _dt * 1.0f;
		_enemy.Move({ sin(m_angle) * 2.5f, m_speed * _dt});
		break;

	case Movement::Spiral:
		m_angle += 3.1415f * _dt * 1.0f;
		_enemy.Move({cos(m_angle) * 2.5f, sin(m_angle) * 2.5f + m_speed * 0.5f * _dt });
		break;

	default:
		break;
	}
}

bool Enemy::CheckCollision(Unit& _other)
{
	return (glm::distance(GetPosition(), _other.GetPosition())) < GetSize() + _other.GetSize();
}

void Enemy::Draw(Resources& _resources)
{
	glm::vec2 size(GetSize());
	draw::Sprite(_resources, tx::Circle, GetPosition() + size / 2.0f, size, GetColor());
}

void Enemy::Move(glm::vec2 _offset)
{
	SetPosition(GetPosition() + _offset);
}

void Enemy::CreateMovement(Movement::Type _type, float _speed)
{
	m_movement.Create(_type, _speed);
}

void Enemy::MovementProcess(const float& _dt)
{
	m_movement.Process(*this, _dt);
}

bool Player::CheckCollision(Unit& _other)
{
	return m_box.CheckCollision(_other);
}

void Player::Draw(Resources& _resources)
{
	glm::vec2 size(GetSize());
	draw::Sprite(_resources, tx::Circle, GetPosition() + size / 2.0f, size, GetColor());

	m_box.Draw(_resources);
}

void Player::SetBoxPosition(glm::vec2 _pos)
{
	m_box.SetPosition(_pos);
}

void Player::SetBoxPosition(float _x, float _y)
{
	SetBoxPosition({ _x, _y });
}

void Player::SetBoxSize(float _size)
{
	m_box.SetSize(_size);
}

void Player::SetBoxColor(glm::vec4 _col)
{
	m_box.SetColor(_col);
}

void Player::SetBoxColor(float _r, float _g, float _b, float _a)
{
	SetBoxColor({ _r, _g, _b, _a });
}

void Player::Move(float _offset)
{
	SetPosition(GetPosition() + glm::vec2(_offset, 0.0f));
	m_box.SetPosition(m_box.GetPosition() + glm::vec2(_offset, 0.0f));
}

EnemySpawner::EnemySpawner()
	: m_counter(0)
	, m_timeline(0.0f)
	, m_move_speed(60.0f)
	, m_spawn_speed(3.0f)
{
}

EnemySpawner::~EnemySpawner()
{
	for (auto& elem : m_enemy_list)
		if (elem) delete elem;
}

void EnemySpawner::Prepare()
{
	for (auto& elem : m_pending_list)
		if (elem) m_enemy_list.remove(elem);

	m_pending_list.clear();
}

void EnemySpawner::MovementProcess(const float& _dt)
{
	for (auto& enemy : m_enemy_list)
		if (enemy) enemy->MovementProcess(_dt);
}

Enemy* EnemySpawner::Create(const float& _dt)
{
	m_timeline += _dt;
	if (m_timeline < m_spawn_speed) return nullptr;

	m_timeline = 0.0f;
	if (m_counter > 10)
	{
		m_counter = 0;
		m_spawn_speed -= 0.01f;
		if (m_spawn_speed < 0.05f) m_spawn_speed = 0.05f;
		m_move_speed += 10.0f;
	}

	GLFWwindow* glfw_window = glfwGetCurrentContext();
	int win_width, win_height;
	glfwGetWindowSize(glfw_window, &win_width, &win_height);
	float win_w = (float)win_width;

	float elem_size = 50.0f;

	//
	static std::random_device rd;
	static std::mt19937 eng(rd());
	std::uniform_real_distribution<float> dist(elem_size, win_w - elem_size * 2.0f);

	//
	static std::random_device rd_col;
	static std::mt19937 eng_col(rd_col());
	std::uniform_real_distribution<float> col(0.0f, 1.0f);

	//
	static std::random_device rd_move;
	static std::mt19937 eng_move(rd_move());
	std::uniform_real_distribution<float> move(0.0, 2.0f);
	Movement::Type move_type = (Movement::Type)roundf(move(eng_move));

	//
	Enemy* enemy = new Enemy();
	enemy->SetPosition(dist(eng), elem_size);
	enemy->SetSize(elem_size);
	enemy->SetColor(col(eng_col), col(eng_col), col(eng_col));
	enemy->CreateMovement(move_type, m_move_speed);

	m_enemy_list.push_back(enemy);
	return enemy;
}

void EnemySpawner::Remove(Enemy* _enemy)
{
	m_pending_list.push_back(_enemy);
	m_counter++;
}

std::list<Enemy*>& EnemySpawner::GetList()
{
	return m_enemy_list;
}
