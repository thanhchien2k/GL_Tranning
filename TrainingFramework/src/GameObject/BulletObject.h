#pragma once
#include "Sprite2D.h"

class BulletObject : public Sprite2D
{	
public:
	BulletObject();
	~BulletObject();

	int get_type() const { return m_typeBullet; }
	void set_type(const int& type) { m_typeBullet = type; }

	bool get_ismove() const { return m_isMove;}
	void set_ismove(bool ismove) { m_isMove = ismove; }

private:
	GLint			m_iHeight;
	GLint			m_iWidth;
	bool			m_isMove;
	GLint			m_typeBullet;
};