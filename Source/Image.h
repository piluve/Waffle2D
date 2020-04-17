#pragma once

namespace Waffle
{
	class Graphics;
	class Image
	{
		friend Graphics;
	public:
		Image();
		~Image();
		static Image* CreateFromFile(const char* path);
		int GetWidth()const;
		int GetHeight()const;

	private:
		unsigned int m_imageID;
		int m_width;
		int m_height;
	};
}