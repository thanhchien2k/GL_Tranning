#pragma once

#include "BaseObject.h"
#include "Sprite2D.h"
#include "SpriteAnimation.h"
#include "GameStates/GameStateBase.h"

class ShipObject : public BaseObject,
					public Sprite2D,
					public SpriteAnimation
{
public:
	ShipObject();
	~ShipObject();
	GLint			m_iHeight;
	GLint			m_iWidth;

	void	HandleMouseMoveEvents(GLint x, GLint y);
	void	HandleKeyEvents(GLint key, bool bIsPressed);

private:
	bool	m_isMoving;

};