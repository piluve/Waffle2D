#include "Graphics.h"
#include "Sprite.h"
#include "Input.h"
#include "Image.h"

using namespace Waffle;

int main()
{
	Graphics& graphics = Graphics::Get();
	graphics.Init();

	Image* img = Image::CreateFromFile("../../Data/Waffle/Img/ColorChecker.png");
	
	Sprite spriteImg(512, 256, img);
	spriteImg.SetPosition(200.0f, 50.0f);
	float rot = 0.0f;
	
	Sprite spriteImg2(spriteImg);
	spriteImg2.SetPosition(-200.0f, -50.0f);

	while (!graphics.Closed())
	{
		if (Input::Get().GetKeyPressed(InputState::Key::Space))
		{
			rot += 10.0f;
			spriteImg.SetRotation(rot);
			spriteImg2.SetRotation(-rot);
		}
		
		graphics.ClearScreen(0.5f, 0.5f, 0.5f, 1.0f);
		graphics.DrawSprite(&spriteImg2);
		graphics.DrawSprite(&spriteImg);
		graphics.Flush();
	}
	return 0;
}