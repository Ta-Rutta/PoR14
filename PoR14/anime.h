#pragma once

class AnimatedObject
{
private:
	Texture spriteSheet;                      // スプライトシート
	Vec2 frameSize;                           // 一つのフレームの大きさ
	std::map<String, Array<Rect>> animations; // アニメーションを管理するマップ
	std::map<String, int32> animationIndices; // アニメーションの現在のインデックスを管理するマップ
	std::map<String, double> animationRates;  // アニメーションの更新レートを管理するマップ
	std::map<String, double> animationTimers; // アニメーションの経過時間を管理するマップ
	std::map<String, bool> loopFlags;         // アニメーションのループフラグを管理するマップ
	String currentAnimation;                  // 現在のアニメーションの名前

public:
	// コンストラクタ
	// @param spriteSheetPath スプライトシートのファイルパス
	// @param frameSize 一つのフレームの大きさ
	AnimatedObject(const String& spriteSheetPath, const Vec2& frameSize)
		: spriteSheet(Texture{ spriteSheetPath }), frameSize(frameSize) {
	}

	// アニメーションを追加するメソッド
	// @param animationName 追加するアニメーションの名前
	// @param row スプライトシート上のアニメーションが配置されている行
	// @param frameCount アニメーションのフレーム数
	// @param rate アニメーションの更新レート（省略可能、デフォルト値は0.5）
	// @param loop アニメーションをループするかどうか（省略可能、デフォルト値は true）
	void addAnimation(const String& animationName, int32 row, int32 frameCount, double rate = 0.5, bool loop = true)
	{
		Array<Rect> frames;
		for (int32 i = 0; i < frameCount; ++i)
		{
			frames.push_back(Rect{ static_cast<int32>(frameSize.x * i), static_cast<int32>(frameSize.y * row), static_cast<int32>(frameSize.x), static_cast<int32>(frameSize.y) });
		}
		animations[animationName] = frames;
		animationIndices[animationName] = 0;
		animationRates[animationName] = rate;
		animationTimers[animationName] = 0.0;
		loopFlags[animationName] = loop;

		// 初期状態のアニメーションを設定
		if (currentAnimation.isEmpty())
		{
			currentAnimation = animationName;
		}
	}

	// アニメーションを更新するメソッド
	void updateAnimation()
	{
		animationTimers[currentAnimation] += Scene::DeltaTime();
		if (animationTimers[currentAnimation] > animationRates[currentAnimation])
		{
			if (animationIndices[currentAnimation] < animations[currentAnimation].size() - 1)
			{
				animationIndices[currentAnimation]++;
			}
			else
			{
				if (loopFlags[currentAnimation])
				{
					animationIndices[currentAnimation] = 0;
				}
			}
			animationTimers[currentAnimation] = 0.0;
		}
	}

	// アニメーションを描画するメソッド
	// @param scale 描画時の拡大率（省略可能、デフォルト値は1.0）
	// @param pos 描画位置（省略可能、デフォルト値は(0, 0)）
	void draw(double scale = 1.0, Vec2 pos = Vec2{ 0, 0 }) const
	{
		const Rect& currentFrame = animations.at(currentAnimation)[animationIndices.at(currentAnimation)];
		spriteSheet(currentFrame).scaled(scale).drawAt(pos);
	}

	// アニメーションを切り替えるメソッド
	// @param animationName 切り替えるアニメーションの名前
	void switchAnimation(const String& animationName)
	{
		if (animations.count(animationName) && currentAnimation != animationName)
		{
			resetAnimation();
			currentAnimation = animationName;
		}
	}

	// アニメーションをリセットするメソッド
	void resetAnimation()
	{
		animationIndices[currentAnimation] = 0;
		animationTimers[currentAnimation] = 0.0;
	}
};

