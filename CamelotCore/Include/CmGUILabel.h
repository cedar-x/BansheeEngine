#pragma once

#include "CmPrerequisites.h"
#include "CmGUIElement.h"

namespace CamelotEngine
{
	class CM_EXPORT GUILabel : public GUIElement
	{
	protected:
		/**
		 * @copydoc GUIElement::getNumRenderElements()
		 */
		virtual UINT32 getNumRenderElements() const;

		/**
		 * @copydoc GUIElement::getMaterial()
		 */
		virtual const MaterialHandle& getMaterial(UINT32 renderElementIdx) const;

		/**
		 * @copydoc GUIElement::getNumQuads()
		 */
		virtual UINT32 getNumQuads(UINT32 renderElementIdx) const;

		/**
		 * @copydoc GUIElement::fillBuffer()
		 */
		virtual void fillBuffer(Vector2* vertices, Vector2* uv, UINT32* indices, UINT32 startingQuad, UINT32 maxNumQuads, UINT32 renderElementIdx) const;
	private:
		friend class GUI;

		GUILabel(const String& text, const FontPtr& font, UINT32 fontSize);

		TextSprite* mTextSprite;
		String mText;
	};
}