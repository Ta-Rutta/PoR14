#pragma once
enum CoolTimeID
{
	GCD, //共通クールタイム
	IND  //個別クールタイム
};

class CoolTime
{
private:
	double timer = 0;
	double coolTime;
	CoolTimeID cooltimeID;

public:
	CoolTime(CoolTimeID coolTimeID, double time)
		:coolTime(guardCoolTime(time))
	{
		
	}

	static double guardCoolTime(double time)
	{
		if (time < 0)throw std::invalid_argument("不正値です。0以上の値を入れなさい。");
		else return time;
	}

	static double guardCoolTimeID(CoolTimeID coolTimeID)
	{
		if (coolTimeID != CoolTimeID::GCD && coolTimeID != CoolTimeID::IND)throw std::invalid_argument("不正値です。クールタイムIDはGCDかIND");
		else return coolTimeID;
	}

	void coolTimeSet() { timer = coolTime; }

	void coolTimeCount()
	{
		const double t = Scene::DeltaTime();
		if (timer > 0)timer -= t;
	}

	bool isReady()
	{
		if (timer <= 0)return true;
		else return false;
	}

};

