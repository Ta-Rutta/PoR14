#pragma once
#include "State.h"

class LogBox
{
public:
	RectF rect;            // ログボックスの表示領域（位置とサイズ）
	double scrollY = 0.0;  // スクロール量
	Array<String> logs;    // ログ文字列の配列

	LogBox(const RectF& _rect) : rect(_rect) {}

	// ログの追加
	void addLog(const String& text);

	// 描画処理
	void draw(const Font& font);
};

