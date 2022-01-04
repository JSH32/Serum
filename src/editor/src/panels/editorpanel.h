#pragma once

namespace Serum2D::Editor {
    class EditorPanel {
    public:
        void Update();

        virtual void OnUpdate() = 0;
    protected:
        bool focus = false;
    };
}