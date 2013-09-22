#pragma once

#include "BsPrerequisites.h"
#include "BsGUIElementBase.h"
#include "BsGUILayoutOptions.h"
#include "CmRect.h"
#include "CmInt2.h"

namespace BansheeEngine
{
	class BS_EXPORT GUIElement : public GUIElementBase
	{
	public:
		GUIElement(GUIWidget& parent, const GUIElementStyle* style, const GUILayoutOptions& layoutOptions, bool acceptsKeyboardFocus = true);
		virtual ~GUIElement();

		/**
		 * @brief	Returns the number of separate render elements in the GUI element.
		 * 			
		 * @note	GUI system attempts to reduce the number of GUI meshes so it will group
		 * 			sprites based on their material and textures. One render elements represents a group
		 * 			of such sprites that share a material/texture.
		 *
		 * @return	The number render elements.
		 */
		virtual CM::UINT32 getNumRenderElements() const = 0;

		/**
		 * @brief	Gets a material for the specified render element index.
		 * 			
		 * @see getNumRenderElements()
		 * 		
		 * @return	Handle to the material.
		 */
		virtual const CM::HMaterial& getMaterial(CM::UINT32 renderElementIdx) const = 0;

		/**
		 * @brief	Returns the number of quads that the specified render element will use. You will need this
		 * 			value when creating the buffers before calling "fillBuffer.
		 * 			
		 * @see getNumRenderElements()
		 * @see fillBuffer()
		 * 		
		 * @note	Number of vertices = Number of quads * 4
		 *			Number of indices = Number of quads * 6
		 *			
		 * @return	Number of quads for the specified render element. 
		 */
		virtual CM::UINT32 getNumQuads(CM::UINT32 renderElementIdx) const = 0;

		/**
		 * @brief	Fill the pre-allocated vertex, uv and index buffers with the mesh data for the
		 * 			specified render element.
		 * 			
		 * @see getNumRenderElements()
		 * @see	getNumQuads()
		 *
		 * @param	vertices			Previously allocated buffer where to store the vertices.
		 * @param	uv					Previously allocated buffer where to store the uv coordinates.
		 * @param	indices				Previously allocated buffer where to store the indices.
		 * @param	startingQuad		At which quad should the method start filling the buffer.
		 * @param	maxNumQuads			Total number of quads the buffers were allocated for. Used only
		 * 								for memory safety.
		 * @param	vertexStride		Number of bytes between of vertices in the provided vertex and uv data.
		 * @param	indexStride			Number of bytes between two indexes in the provided index data.
		 * @param	renderElementIdx	Zero-based index of the render element.
		 */
		virtual void fillBuffer(CM::UINT8* vertices, CM::UINT8* uv, CM::UINT32* indices, CM::UINT32 startingQuad, 
			CM::UINT32 maxNumQuads, CM::UINT32 vertexStride, CM::UINT32 indexStride, CM::UINT32 renderElementIdx) const = 0;

		/**
		 * @brief	Recreates the internal render elements. Must be called before fillBuffer if element is dirty. 
		 * 			Marks the element as non dirty.
		 */
		void updateRenderElements();

		/**
		 * @brief	Gets non-clipped bounds that were assigned to the element by the parent layout.
		 */
		CM::Rect getBounds() const;

		virtual bool mouseEvent(const GUIMouseEvent& ev);
		virtual bool keyEvent(const GUIKeyEvent& ev);
		virtual bool commandEvent(const GUICommandEvent& ev);

		static void destroy(GUIElement* element);

		/************************************************************************/
		/* 							INTERNAL METHODS                      		*/
		/************************************************************************/

		void _setWidgetDepth(CM::UINT8 depth);
		void _setAreaDepth(CM::UINT16 depth);
		void _setOffset(const CM::Int2& offset);
		void _setWidth(CM::UINT32 width);
		void _setHeight(CM::UINT32 height);
		void _setClipRect(const CM::Rect& clipRect);
		void _setAcceptsKeyboardFocus(bool acceptsKeyboardFocus) { mAcceptsKeyboardFocus = acceptsKeyboardFocus; }
		virtual void _setFocus(bool focus) {}
		virtual void _changeParentWidget(GUIWidget* widget);

		CM::UINT32 _getWidth() const { return mWidth; }
		CM::UINT32 _getHeight() const { return mHeight; }
		CM::Int2 _getOffset() const { return mOffset; }
		virtual CM::UINT32 _getRenderElementDepth(CM::UINT32 renderElementIdx) const { return _getDepth(); }
		Type _getType() const { return GUIElementBase::Type::Element; }
		bool _isDestroyed() const { return mIsDestroyed; }

		const CM::Rect& _getClippedBounds() const { return mClippedBounds; }
		CM::UINT32 _getDepth() const { return mDepth; }
		GUIWidget& _getParentWidget() const { return *mParent; }
		virtual bool _isInBounds(const CM::Int2 position) const;
		bool _acceptsKeyboardFocus() const { return mAcceptsKeyboardFocus; }

		virtual const GUIContextMenu* getContextMenu() const { return nullptr; }

		/**
		 * @brief	Returns a clip rectangle relative to the element, used for offsetting
		 * 			the input text.
		 */
		virtual CM::Int2 _getTextInputOffset() const { return CM::Int2(); }

		/**
		 * @brief	Returns a clip rectangle relative to the element, used for clipping
		 * 			the input text.
		 */
		virtual CM::Rect _getTextInputRect() const { return CM::Rect(); }

		const GUILayoutOptions& _getLayoutOptions() const { return mLayoutOptions; }
	protected:
		virtual void updateRenderElementsInternal();
		virtual void updateClippedBounds() = 0;

		void setLayoutOptions(const GUILayoutOptions& layoutOptions);
		
		CM::Rect getVisibleBounds() const;
		CM::Rect getContentBounds() const;
		CM::Rect getContentClipRect() const;

		static GUILayoutOptions getDefaultLayoutOptions(const GUIElementStyle* style);

		GUIWidget* mParent;
		bool mIsDestroyed;
		GUILayoutOptions mLayoutOptions;
		CM::Rect mClippedBounds;

		bool mAcceptsKeyboardFocus;
		CM::UINT32 mDepth;
		CM::Int2 mOffset;
		CM::UINT32 mWidth, mHeight;
		CM::Rect mClipRect;
		const GUIElementStyle* mStyle;
	};
}