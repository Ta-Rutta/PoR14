#pragma once
class SkillValue
{
private:
	int value;
	int comboValue;
public:
	SkillValue(int val, int comboVal)
	{
		if (val < 0)throw std::out_of_range("威力は0以上にしてね");
		if (comboVal < 0)throw std::out_of_range("コンボ時の威力は0以上にしてね");
		value = val;
		comboValue = comboVal;
	}

	int returnSkillValue()
	{
		return value;
	}

	int returnComboValue()
	{
		return comboValue;
	}

};

