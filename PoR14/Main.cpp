# include <Siv3D.hpp> // Siv3D v0.6.14
# include "effect.h"
# include "SkillManager.h"
# include "common.cpp"
# include "anime.h"
# include "practice.h"
# include "Talk.h"
#include "UIManager.h"

//using App = SceneManager<String>;//using=省略
bool once = true;
enum class EntityState { playerSide, enemySide };//シーン管理{0,1}
class EntityManager;
class Player;
class Enemy;
class PlayerAct;
class SkillManager;


ColorF changeColor(double t, double limit) {

	if (t < limit * 0.1) {
		return ColorF(1.0, 0.9, 0.0, 0.4);
	}
	else if (limit * 0.1 <= t && t < limit - 0.5) {
		return ColorF(1.0, 0.9 - 0.3 * t, 0.0, 0.4);
	}
	else {
		return ColorF(1.0, 0, 0.0, 0.4);
	}

}

ColorF colorFrame(double t, double limit) {

	if (t < limit * 0.1) {
		return ColorF(1.0, 0.9, 0.0, 0.7);
	}
	else if (limit * 0.1 <= t && t < limit - 0.5) {
		return ColorF(1.0, 0.9 - 0.3 * t, 0.0, 0.7);
	}
	else {
		return ColorF(1.0, 0, 0.0, 0.7);
	}

}


void reBool(bool& a) {
	if (a == false)a = true;
}


void drawRect(int x, int y, double t, int wide, int length) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	RectF{ Arg::center(x, y), change * wide, change * length }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		RectF{ Arg::center(x, y), change2 * wide, change2 * length }.draw(changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		RectF{ Arg::center(x, y), change3 * wide, change3 * length }.draw(changeColor(t, 3));
	}
}

void drawCircle(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.draw(changeColor(t, 3)).drawFrame(10, 0, changeColor(t, 3), colorFrame(t, 3));;
	}
}


void drawDonut(int x, int y, double t, int r, int wide) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawFrame(wide, 0, changeColor(t, 3), colorFrame(t, 3));;

}

void drawBlethRight(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawPie(75_deg, 30_deg, changeColor(t, 3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.drawPie(75_deg, 30_deg, changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.drawPie(75_deg, 30_deg, changeColor(t, 3));
	}
}

void drawBlethLeght(int x, int y, double t, int r) {
	double pro = Min(t, 1.0);
	const double change = EaseOutQuart(pro);
	Circle{ Arg::center(x, y), change * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	if (1 < t && t <= 2) {
		double pro2 = Min(t - 1, 1.0);
		const double change2 = EaseOutQuart(pro2);
		Circle{ Arg::center(x, y), change2 * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	}
	if (2 < t && t < 3) {
		double pro3 = Min(t - 2, 1.0);
		const double change3 = EaseOutQuart(pro3);
		Circle{ Arg::center(x, y), change3 * r }.drawPie(255_deg, 30_deg, changeColor(t, 3));
	}
}

RectF returnRect(int x, int y, int wide, int height) {
	return RectF{ Arg::center(x, y), wide, height };
}

Circle returnCircle(int x, int y, int r) {
	return Circle{ Arg::center(x, y) ,r };
}

double returnRadi(Vec2 attacker, Vec2 damager) {
	Vec2 direction = damager - attacker;
	return Math::Atan2(direction.y, direction.x);
}

class TextDisplay
{
public:
	const Font font{ FontMethod::MSDF,50 };

	void drawTitle()
	{

	}
};

class Entity {
public:
	int hp;
	int r;
	double t;
	EntityManager* manager;
	EntityState state;
	Circle area;
	Vec2 pos;
	Entity* target;
	bool targeted = false;
	int exp;
	int Lv;


	virtual void update() = 0;
	virtual void draw()const = 0;
	virtual Circle getHitbox()const = 0;
	virtual void setTarget(Entity* target) = 0;

	Entity(EntityManager* manager, EntityState state, Vec2 pos, int lv)
		:manager{ manager }, state{ state }, pos{ pos }, Lv{ lv }
	{

	}


	EntityState getState()const
	{
		return state;
	}

	void Targeted(bool t) {
		targeted = t;
	}

	void damage(int damage) {
		hp -= damage;
	}

	virtual void getExp(int exp) {};

};


class EntityManager {
public:
	Effect effect;
	Array<std::shared_ptr<Entity>>entitys;
	Array<std::shared_ptr<Player>>player;
	Array<std::shared_ptr<Enemy>>enemy;
	HashTable<EntityState, Array<Entity*>>entityTable;
	const Font font{ 40, Typeface::CJK_Regular_JP };

	void add(Entity* entity)//配列につっこむ
	{
		auto sharedEntity = std::shared_ptr<Entity>(entity);

		entitys.push_back(sharedEntity);
		if (entity->getState() == EntityState::playerSide)
		{
			// Entity型 -> Player型へキャストして追加
			player.push_back(std::static_pointer_cast<Player>(sharedEntity));
		}
		else
		{
			// Entity型 -> Enemy型へキャストして追加
			enemy.push_back(std::static_pointer_cast<Enemy>(sharedEntity));
		}
		entityTable[entity->state].push_back(entity);
	}

	Array<Entity*> get(EntityState state)
	{
		if (entityTable.contains(state))
		{
			return entityTable[state];
		}

		return Array<Entity*>{};
	}

	void removeEntitytable(Entity* entity)
	{
		EntityState state;
		state = entity->getState();
		entityTable[state].remove(entity);
	}

	void update()
	{
		
		for (auto& entity : entitys)
		{
			entity->update();

			if (entity->getHitbox().leftClicked())
			{
				for (auto& entity2 : entitys)
				{
					entity2->Targeted(false);
				}

				entity->Targeted(true);

				if (not entitys.isEmpty())
				{
					entitys[0]->setTarget(entity.get());
				}
			}
			
		}

		if (MouseR.down())
		{
			for (auto& e : entitys)
			{
				e->Targeted(false);
			}

			if (not entitys.isEmpty())
			{
				entitys[0]->setTarget(nullptr);
			}
		}

		entitys.remove_if([&](const std::shared_ptr<Entity>& entity)
		{
			if (entity->hp <= 0)
			{
				removeEntitytable(entity.get());
				return true;
			}
			return false;
		}
		);

	}

	void draw()const
	{
		for (auto& entity : entitys)
		{
			entity->draw();
		}
	}	
};

class Player : public Entity
{
public:
	bool move = true;
	bool debuff = false;
	AnimatedObject motion{ U"Assets/rutta_walkL.png",Vec2{120,160} };
	SkillManager skillManager;


	Player(EntityManager* manager, EntityState state, Vec2 pos, int lv)
		:Entity{ manager,state,pos,lv }
	{
		hp = 10000;
		r = 5;
		t = 0;
		motion.addAnimation(U"walk", 0, 3, 0.1, true);
	}


	void update()
	{
		skillManager.update();
		motion.updateAnimation();
		const double deltaTime = Scene::DeltaTime();
		t += deltaTime;
		area = { pos,r };

		if (move == true)
		{
			Vec2 inputDir{ 0.0, 0.0 };

			if (KeyD.pressed()) inputDir.x += 1.0;
			if (KeyA.pressed()) inputDir.x -= 1.0;
			if (KeyS.pressed()) inputDir.y += 1.0;
			if (KeyW.pressed()) inputDir.y -= 1.0;

			// 2. 入力があった場合だけ処理する
			if (not inputDir.isZero())
			{
				// setLength(300) で、ベクトルの長さを「斜めであってもなくても常に300」に固定する！
				pos += inputDir.setLength(300) * deltaTime;

			}

			// X座標とY座標をそれぞれ個別に制限する
			/*pos.x = std::clamp(pos.x, 200.0, 1720.0);
			pos.y = std::clamp(pos.y, 200.0, 1000.0);*/
		}


	}
	void drawTargeted()const
	{
		Circle{ pos,r + 15 }.drawFrame(5, 0, ColorF(1, 0, 0));
	}

	void getExp(int exp)
	{
		this->exp += exp;
	}

	void draw()const
	{

		if (target != nullptr)Print(target->pos.distanceFrom(pos));
		Print(pos);
		motion.draw(0.75, { pos.x,pos.y - 50 });
		area.draw();

	}

	SkillResult getSkillClicked(SkillType type)
	{
		return skillManager.returnSkillResult(type);
	}

	Circle getHitbox()const
	{
		return Circle{ pos,r + 10 };
	}

	void damage()
	{
		hp -= 1;
	}

	int returnHP()
	{
		return hp;
	}

	Vec2 returnPos()
	{
		return pos;
	}

	void stop()
	{
		move = false;
	}

	void remove()
	{
		move = true;
	}

	void setTarget(Entity* Target)
	{
		target = Target;
	}

	void untarget()
	{
		target = nullptr;
	}

};


class Enemy :public Entity
{
public:
	bool move = true;

	double distance = 0;
	Vec2 velocity{ 0, 0 };
	Circle detection{ pos,r + 20 };
	Circle cougi;
	Polygon ougi;
	double AttackTimer = 0;
	double autoAttack = 0;
	double time = 0;
	

	Enemy(EntityManager* manager, EntityState state, Vec2 pos, int lv)
		:Entity{ manager,state,pos,lv }
	{
		hp = 10000;
		r = 100;
		t = 0;
	}

	void update()
	{
		cougi = { pos,300 };

		if (target != nullptr)
		{
			double DeltaTime = Scene::DeltaTime();
			time += DeltaTime;

			/*if (RectF::FromPoints({ 200, 200 }, { 1720,1000 }).intersects(target->pos))
			{
				printf("Yes");
			}*/
			Print(RectF::FromPoints({ 200, 200 }, { 1720,1000 }).intersects(target->pos));
			double targetRadi = returnRadi(pos, target->pos);
			constexpr double halfFan = 30_deg / 2.0;
			ougi = cougi.pieAsPolygon(targetRadi-halfFan, 30_deg);
		}

		area = { pos,r };
		detection = { pos,r + 20 };

		if (move)
		{
			if (target != nullptr)
			{
				const double deltaTime = Scene::DeltaTime();
				AttackTimer += deltaTime;
				autoAttack += deltaTime;

				pos = moveAct();//敵の追従スピード0.2が最適
				attack(AttackTimer, &autoAttack);
			}
			else
			{
				autoAttack = 0;
			}
		}
	}

	virtual void attack(double AttackTimer,double* AutoAttack)
	{
		if (*AutoAttack >= 0.5)
		{
			target->damage(3);
			manager->effect.add<DamageEffectE>(target->pos, 3, manager->font, U"a");
			*AutoAttack = 0;
		}

		//if(3<AttackTimer)
	}

	virtual Vec2 moveAct()
	{
		return Math::SmoothDamp(pos, toTarget(pos, target->pos, 35), velocity, 0.2);
	}

	void drawTargeted()const
	{
		Circle{ pos,r + 15 }.drawFrame(5, 0, ColorF(1, 0, 0));
	}

	void draw()const
	{

		if (targeted == true)drawTargeted();
		
		if (target != nullptr)
		{
			Circle{ pos,r }.draw(Palette::Red);
		}
		else
		{
			Circle{ pos,r }.draw(Palette::White);
		}
	}

	void serchTarget()
	{
		for (auto& player : manager->get(EntityState::playerSide))
		{
			if (player->area.intersects(Circle{ pos,r + 100 }))
			{
				setTarget(player);
			}
		}
	}

	Vec2 toTarget(const Vec2& startPos, const Vec2& targetPos, double length)
	{
		return targetPos + (startPos - targetPos).setLength(length);
	}

	Circle getHitbox()const
	{
		return Circle{ pos,r + 50 };
	}

	void setTarget(Entity* Target)
	{
		target = Target;
	}

};

class Boss :public Enemy
{
public:

	Boss(EntityManager* manager, EntityState state, Vec2 pos, int lv)
		: Enemy{ manager, state, pos, lv } 
	{
		hp = 50000;
	}

	Vec2 moveAct() override
	{
		return pos;
	}
	
};

class Mokujin :public Enemy
{
public:
	Vec2 moveAct() override
	{
		return pos;
	}
};

class Shadow :public Enemy
{
public:
	Vec2 moveAct() override
	{
		return Math::SmoothDamp(pos, toTarget(pos, target->pos, 35), velocity, 0.2);
	}
};




class Title : public App::Scene
{
public:
	EntityManager manager;
	Player* player = new Player{ &manager, EntityState::playerSide, Scene::Center() ,1 };
	bool move = false;
	const Font font{ FontMethod::MSDF,50};
	double a = 0;
	double time = 0;
	TalkWindow talk;

	


	Title(const InitData& init)
		: IScene{ init }
	{
		player->stop();
		
		talk.addTalk(U"？？？", U"こんにちは");
		talk.addTalk(U"プレイヤー", U"さようなら");
		talk.addTalk(U"？？？", U"このように、文章の途中でスキップすることもできます。");
	}

	void update()override {
		if (move)time += Scene::DeltaTime() * 0.9;
		const double t = (1 - Min(time, 1.0));

		Scene::SetBackground(Palette::Black);
		if (KeyEnter.down()) {
			player->remove();
			move = true;
		}
		
		a = EaseOutSine(t);
		
		player->update();
		talk.update(MouseL.down() || KeyEnter.down());
	}

	void draw()const override
	{
		font(U"Enterキーでスタート！").drawAt(Scene::Center(), ColorF{ 1,1,1,a});
		player->draw();
		if(!talk.isContinue())
		talk.draw(RectF{ 500,400,1420,200 });
	}
};

class StoryBattole
{
public:
	EntityManager* manager;
	bool judged[100];
	

	StoryBattole(EntityManager* ma)
		:manager{ma}
	{
		for (int i = 0; i < 100; i++)judged[i] = false;

	}

	bool checkCircle(Vec2 playerPos,Vec2 pos, double r)
	{
		Ellipse area = Ellipse{ pos,r ,r-30};
		area.draw();
		return area.intersects(playerPos);
	}

	bool checkRect(Vec2 playerPos, Vec2 pos, double w,double h)
	{
		RectF area = RectF{ pos,w ,h };
		area.draw();
		return area.intersects(playerPos);
	}

	void update(double time)
	{
		Vec2 Pos = manager->entitys[0]->pos;

		/*if (time >= 2 && !judged)
		{
			if (checkCircle(Pos, { 300, 300 }, 100))
			{
				manager->entitys[0]->hp -= 1;
				Circle{ { 300, 300 }, 100 }.draw();
			}
			judged[0] = true;
		}*/

		if (/*time >= 5*/ Key1.down()/* && !judged*/)
		{
			if (checkCircle(Pos, { 300, 300 }, 100))
			{
				manager->entitys[0]->hp -= 1;
			}
			/*judged[1] = true;*/
		}

		if (/*time >= 5*/ Key2.down()/* && !judged*/)
		{
			if (checkRect(Pos, { 300, 300 }, 100,100))
			{
				manager->entitys[0]->hp -= 1;
			}
			/*judged[1] = true;*/
		}
	}


};

class Battle : public App::Scene
{
public:
	EntityManager* manager;

	Battle(const InitData& init)
		: IScene{ init }
	{		
			
	}
	

	

	void update()override
	{
		
		

	}

	void draw() const override
	{
		
		
	}
};

class Practice : public App::Scene
{
public:

	EntityManager manager;
	Camera2D camera{ Vec2{ 640, 360 }, 1.0 };
	double timer = 0;
	StoryBattole ba{ &manager };

	Practice(const InitData& init)
		: IScene{ init }
	{

		Scene::SetBackground(Palette::Black);
		manager.add(new Player{ &manager, EntityState::playerSide, Vec2{640,360} ,1 });
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{100,100} ,1 });
		/*manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{200,100},2 });
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{300,100},3 });*/

	}


	void update()override
	{
		timer += Scene::DeltaTime();


		if (not manager.player.isEmpty()) {
			auto& player = *manager.player[0];
			Vec2 targetPos = player.pos;



			if (player.target != nullptr)
			{
				// ターゲットとの中間地点を計算
				targetPos = (player.pos + player.target->pos) / 2.0;
			}
			camera.setTargetCenter(targetPos);
		}

		camera.update();
		{

			// camera.createTransformer() をスコープ内で宣言すると、
			// そのスコープ内でのマウス判定（leftClicked等）がワールド座標基準になります。
			const auto transformer = camera.createTransformer();
			ba.update(timer);
			manager.update();

			for (auto& enemy : manager.enemy) {
				enemy->serchTarget();
			}
		}
	}

	void draw()const override {
		const auto transformer = camera.createTransformer();
		manager.draw();
		manager.effect.update();
		Scene::SetBackground(Palette::Skyblue);


	}
};



class Debug : public App::Scene
{
public:
	UIManager UImanager;
	EntityManager manager;
	Camera2D camera{ Vec2{ 960,600 },0.8};
	double timer=0;
	StoryBattole ba{ &manager };

	Debug(const InitData& init)
		: IScene{ init }
	{
		
		Scene::SetBackground(Palette::Black);
		manager.add(new Player{ &manager, EntityState::playerSide, Vec2{960,600} ,1 });
		manager.add(new Boss{ &manager, EntityState::enemySide, Vec2{960,100} ,1 });
		/*manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{200,100},2 });
		manager.add(new Enemy{ &manager, EntityState::enemySide, Vec2{300,100},3 });*/
	}


	void update()override
	{
		if (KeyP.down())changeScene(U"Practice");

		timer += Scene::DeltaTime();
		HpProcess();
		
		if (not manager.player.isEmpty()) {
			auto& player = *manager.player[0];
			Vec2 targetPos = player.pos;

			

			if (player.target != nullptr)
			{
				// ターゲットとの中間地点を計算
				targetPos = (player.pos + player.target->pos) / 2.0;
			}
			camera.setTargetCenter(targetPos);
		}

		camera.update();
		{	
			// camera.createTransformer() をスコープ内で宣言すると、
			// そのスコープ内でのマウス判定（leftClicked等）がワールド座標基準になります。
			const auto transformer = camera.createTransformer();
			ba.update(timer);
			manager.update();

			for (auto& enemy : manager.enemy) {
				enemy->serchTarget();
			}
		}
	}

	void HpProcess()
	{
		SkillType type = UImanager.checkClicked();

		SkillResult result;

		if (type != SkillType::None)
		{
			result = manager.player[0]->getSkillClicked(type);
			manager.enemy[0]->hp -= result.damage;
		}
	}


	void draw()const override
	{

		{
			const auto transformer = camera.createTransformer();
			RectF::FromPoints({ 200, 200 }, { 1720,1000 }).draw(Palette::Black);
			manager.draw();
			manager.effect.update();
			Scene::SetBackground(Palette::Skyblue);	
		}
		UImanager.draw();
		
		Print(manager.enemy[0]->hp);
	}
};

void Main()
{
	/*Window::Resize(1920, 1200);
	Window::SetStyle(WindowStyle::Sizable);*/

	// 1. ゲーム内の論理解像度を 1920x1200 に固定
	Scene::Resize(1920, 1200);

	// 2. ウィンドウサイズは、ひとまずモニターに入る現実的なサイズ（例: 1280x800 など）にする
	// ※ 1920x1200 のままでも、モニターに合わせて自動縮小されつつ、内部座標は 1920x1200 が維持されます
	Window::Resize(1280, 800);
	Window::SetStyle(WindowStyle::Sizable);

	// ウィンドウサイズが変わってもゲーム内の解像度（1920x1200）とアスペクト比を維持する設定


	App manager;

	//manager.add<Title>(U"Title");
	//manager.add<Battle>(U"Battle");
	manager.add<Debug>(U"Debug");
	manager.add<Debug>(U"Practice");

	while (System::Update())
	{
		if (not manager.update())
		{

			break;
		}
	}
}
