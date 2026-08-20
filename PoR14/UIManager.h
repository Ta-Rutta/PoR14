#pragma once
#include "SkillUI.h"

class UIManager
{
public:
	SkillUI skillUI;

	SkillType checkClicked()
	{
		return skillUI.checkClicked();
	}

	void draw()const
	{
		skillUI.draw();
	}
	
};

