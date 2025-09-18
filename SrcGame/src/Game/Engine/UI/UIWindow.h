#pragma once

#include <memory>
#include "UIElement.h"
#include "UIColor.h"

#include "..\\Keyboard\\Keyboard.h"
#include "..\\Mouse\\Mouse.h"
#include "Utils\\Geometry.h"

namespace UI
{
	typedef std::shared_ptr<class Window> Window_ptr;
	class Window : public Element
	{
	public:
		//Constructor
		Window(Rectangle2D rRectangle);
		virtual ~Window();

		void Clear();

		//Getters and Setters
		int GetType() { return TYPE_Window; };
		void SetImage(class Image* pImage) { this->pImage = pImage; };
		void SetMoveBox(Rectangle2D s) { rRectSelectMove = s; };
		void SetCanMove(BOOL b) { bCanMove = b; };
		void SetScroll(std::shared_ptr<class Scroll> pScroll) { pScrollMain = pScroll; };
		void SetGroup(std::shared_ptr<class Group> pGroup) { pGroupMain = pGroup; };
		void SetEvent(int iEvent) { iEventID = iEvent; };
		void SetEvent(int iEvent, EMouseEvent e) { iEventID = iEvent; eMouseEvent = e; };
		void SetHoverEvent(int iEvent) { iHoverEventID = iEvent; }
		void SetBox(Rectangle2D sBox);
		BOOL IsHover();
		void SetColorBackground(Color c) { cColorBackground = c; }

		void SetFocusWindow(BOOL b) { bFocusWindow = b; }
		BOOL GetFocusWindow() { return bFocusWindow; }

		void Update(float fTime);

		//Render Window
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, int iSourceWidth = -1, int iSourceHeight = -1);

		//Event Handlers
		BOOL OnMouseClick(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseScroll(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnMouseMove(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		BOOL OnKeyChar(CKeyboard* pcKeyboard);
		BOOL OnKeyPress(CKeyboard* pcKeyboard);

		void AddElement(Element_ptr pElement);
		BOOL DelElement(Element_ptr pElement);

		template <class F>
		inline std::shared_ptr<F> GetElement(int iIDObject)
		{
			// Find object and return pointer to this
			for (UINT u = 0; u < vElementsChild.size(); u++)
			{
				if (vElementsChild[u]->GetID() == iIDObject)
				{
					return std::dynamic_pointer_cast<F>(vElementsChild[u]);
				}
			}
			return NULL;
		};
	private:
		class Rectangle2D rRectViewPort;
		class Rectangle2D rRectSelectMove;

		class Image* pImage = NULL;
		int iID = -1;
		int iEventID = -1;
		int iHoverEventID = -1;
		EMouseEvent eMouseEvent = ClickDownL;
		std::shared_ptr<class Group> pGroupMain = NULL;
		std::shared_ptr<class Scroll> pScrollMain = NULL;
		BOOL bSelected = FALSE;
		BOOL bCanMove = FALSE;
		BOOL bIsHover = FALSE;
		BOOL bFocusWindow = TRUE;

		Color cColorBackground = 0;

		Point2D sPointMouse;
	};
}