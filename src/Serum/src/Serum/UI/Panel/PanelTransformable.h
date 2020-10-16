#pragma once

#include "Panel.h"

#include "Serum/UI/Settings/WindowSettings.h"
#include "Serum/UI/Settings/Alignment.h"
#include "Serum/UI/Internal/Converter.h"

namespace Serum::UI {
    class PanelTransformable : public Panel {
    public:
        explicit PanelTransformable(
                glm::vec2 startingPosition = glm::vec2(-1, -1),
                glm::vec2 startingSize = glm::vec2(-1, -1),
                HorizontalAlignment startingHorizontalAlignment = HorizontalAlignment::LEFT,
                VerticalAlignment startingVerticalAlignment = VerticalAlignment::TOP,
                bool ignoreConfig = false
        ) :
                startingPosition(startingPosition),
                startingSize(startingSize),
                startingHorizontalAlignment(startingHorizontalAlignment),
                startingVerticalAlignment(startingVerticalAlignment),
                ignoreConfigFile(ignoreConfigFile) {};

        void SetPosition(const glm::vec2 newPosition);

        void SetSize(const glm::vec2 newSize);

        void SetAlignment(HorizontalAlignment newHorizontalAlignment, VerticalAlignment newVerticalAlignment);

        const glm::vec2 &GetPosition() const;

        const glm::vec2 &GetSize() const;

        HorizontalAlignment GetHorizontalAlignment() const;

        VerticalAlignment GetVerticalAlignment() const;

        bool autoSize = true;
    protected:
        void Update();

        glm::vec2 startingPosition;
        glm::vec2 startingSize;
        HorizontalAlignment startingHorizontalAlignment;
        VerticalAlignment startingVerticalAlignment;
        bool ignoreConfigFile;

        glm::vec2 position = glm::vec2(0, 0);
        glm::vec2 size = glm::vec2(0, 0);

        bool positionChanged = false;
        bool sizeChanged = false;

        HorizontalAlignment horizontalAlignment = HorizontalAlignment::LEFT;
        VerticalAlignment verticalAlignment = VerticalAlignment::TOP;

        bool alignmentChanged = false;
        bool firstFrame = true;
    private:
        glm::vec2 CalculatePositionAlignmentOffset(bool starting = false);

        void UpdatePosition();

        void UpdateSize();

        void CopyImGuiPosition();

        void CopyImGuiSize();
    };
}