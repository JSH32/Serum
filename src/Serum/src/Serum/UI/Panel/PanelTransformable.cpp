#include "PanelTransformable.h"

namespace Serum::UI {
    void PanelTransformable::SetPosition(const glm::vec2 newPosition) {
        position = newPosition;
        positionChanged = true;
    }
    void PanelTransformable::SetSize(const glm::vec2 newSize) {
        size = newSize;
        sizeChanged = true;
    }
    void PanelTransformable::SetAlignment(HorizontalAlignment newHorizontalAlignment,
                                          VerticalAlignment newVerticalAlignment) {
        horizontalAlignment = newHorizontalAlignment;
        verticalAlignment = newVerticalAlignment;
        alignmentChanged = true;
    }
    const glm::vec2 & PanelTransformable::GetPosition() const {
        return position;
    }
    const glm::vec2 & PanelTransformable::GetSize() const {
        return size;
    }
    HorizontalAlignment PanelTransformable::GetHorizontalAlignment() const {
        return horizontalAlignment;
    }
    VerticalAlignment PanelTransformable::GetVerticalAlignment() const {
        return verticalAlignment;
    }
    void PanelTransformable::UpdatePosition() {
        if (startingPosition.x != -1.f && startingPosition.y != 1.f) {
            glm::vec2 offset = startingPosition + CalculatePositionAlignmentOffset(true);
            glm::vec2 offsetPos(position.x + offset.x, position.y + offset.y);
            ImGui::SetWindowPos(Converter::ToImVec2(offsetPos), ImGuiCond_Always);
            positionChanged = false;
            alignmentChanged = false;
        }
    }
    void PanelTransformable::UpdateSize() {
        if (sizeChanged) {
            ImGui::SetWindowSize(Converter::ToImVec2(size), ImGuiCond_Always);
            sizeChanged = false;
        }
    }
    void PanelTransformable::CopyImGuiPosition() {
        position = Converter::ToVec2(ImGui::GetWindowPos());
    }
    void PanelTransformable::CopyImGuiSize() {
        size = Converter::ToVec2(ImGui::GetWindowSize());
    }
    void PanelTransformable::Update() {
        if (firstFrame) {
            if (!autoSize)
                UpdateSize();
            CopyImGuiSize();

            UpdatePosition();
            CopyImGuiPosition();
        }

        firstFrame = false;
    }
    glm::vec2 PanelTransformable::CalculatePositionAlignmentOffset(bool starting) {
        glm::vec2 result(0, 0);

        switch(starting ? startingHorizontalAlignment : horizontalAlignment) {
            case HorizontalAlignment::CENTER:
                result.x -= size.x / 2.0f;
                break;
            case HorizontalAlignment::RIGHT:
                result.x -= size.x;
                break;
        }

        switch(starting ? startingVerticalAlignment : verticalAlignment) {
            case VerticalAlignment::MIDDLE:
                result.y -= size.y / 2.0f;
                break;
            case VerticalAlignment::BOTTOM:
                result.y -= size.y;
                break;
        }

        return result;
    }
}