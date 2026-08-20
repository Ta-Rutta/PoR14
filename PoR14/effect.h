#pragma once

struct DamageEffectP : IEffect
{
	Vec2 m_start;

	int32 m_score;

	Font m_font;

	String m_text;


	DamageEffectP(const Vec2& start, int32 score, const Font& font, const String& text)
		: m_start{ start }
		, m_score{ score }
		, m_font{ font }
		, m_text{ text }
		
	{
	}

	bool update(double t) override
	{
		const double alpha = 1.0 - (t * 1.0);
		const HSV color{ 30, 0.8, 1.0 , alpha};

		m_font(m_text,m_score).drawAt(TextStyle::Outline(1, ColorF{ 0,0,0}),
			40, m_start.movedBy(0,-t * 120), color);

		return (t < 0.5);
	}
};

struct DamageEffectE : IEffect
{
	Vec2 m_start;

	int32 m_score;

	Font m_font;

	String m_text;


	DamageEffectE(const Vec2& start, int32 score, const Font& font, const String& text)
		: m_start{ start }
		, m_score{ score }
		, m_font{ font }
		, m_text{ text }

	{
	}

	bool update(double t) override
	{
		const double alpha = 1.0 - (t * 1.0);
		const HSV color{ 30, 0.8, 1.0 , alpha };
		

		m_font(m_text, m_score).drawAt(TextStyle::Outline(1, ColorF{ 0,0,0 }),
			40, m_start.movedBy(0, t * 120), color);

		return (t < 0.5);
	}
};

struct HealEffect : IEffect
{
	Vec2 m_start;

	int32 m_score;

	Font m_font;

	String m_text;


	HealEffect(const Vec2& start, int32 score, const Font& font, const String& text)
		: m_start{ start }
		, m_score{ score }
		, m_font{ font }
		, m_text{ text }

	{
	}

	bool update(double t) override
	{
		const double alpha = 1.0 - (t * 1.0);
		const HSV color{ 30, 0.8, 1.0 , alpha };


		m_font(m_text, m_score).drawAt(TextStyle::Outline(0.1, ColorF{ 0,0,0 }),
			40, m_start.movedBy(0, -t * 120), color);

		return (t < 0.5);
	}
};
