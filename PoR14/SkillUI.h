#pragma once
#include "SkillID.h"

class SkillUI
{
private:
	double IconSize = 60;

public:
	SkillType type;
	Texture skillIcon;
	Vec2 pos;
	RectF body;
	
	SkillUI(SkillType type, Texture skillIcon, Vec2 pos)
		:type(type), skillIcon(skillIcon), pos(pos)
	{
		body = RectF{ pos,IconSize };
	}
};

class SkillUIRegister
{
public:
	Array<SkillUI> skillUIs;

	SkillUIRegister()
	{
		skillUIs.push_back(SkillUI{ SkillType::Attack,Texture{U"Assets/2026LOGO.png"},Vec2{500,600} });
		skillUIs.push_back(SkillUI{ SkillType::Attack2,Texture{U"Assets/ramen.jpg"},Vec2{570,600} });
	}

	Array<SkillUI> releaseSkillUIs()
	{
		return std::move(skillUIs);
	}
};

class SkillUIManager
{
public:
	Array<SkillUI> skillUIs;

private:	

	void addSkillUI()
	{
		skillUIs.push_back(SkillUI{ SkillType::Attack,Texture{U"Assets/2026LOGO.png"},Vec2{500,600} });
		skillUIs.push_back(SkillUI{ SkillType::Attack2,Texture{U"Assets/ramen.jpg"},Vec2{570,600} });
	}

public:
	SkillUIManager()
	{
		addSkillUI();
	}	

	SkillType checkClicked()
	{
		for (const auto& s : skillUIs)
		{
			if (s.body.leftClicked())
			{
				return s.type;
			}
		}
		return SkillType::None;
	}

	void draw()const
	{
		for (const auto& s : skillUIs)
		{
			s.body(s.skillIcon).draw();
		}
	}

};

