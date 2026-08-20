#pragma once
#include "SkillType.cpp"

class OneSkillUI
{
private:
	double IconSize = 30;

public:
	SkillType type;
	Texture skillIcon;
	Vec2 pos;
	RectF body;
	OneSkillUI(SkillType type, Texture skillIcon, Vec2 pos)
		:type(type), skillIcon(skillIcon), pos(pos)
	{
		body = RectF{ pos,IconSize };
	}
};

class SkillUI
{
public:
	Array<OneSkillUI> skillUIs;

private:	

	void addSkillUI()
	{
		skillUIs.push_back(OneSkillUI{ SkillType::Attack,Texture{U"Assets/baria.bmp"},Vec2{500,600} });
	}

public:
	SkillUI()
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

