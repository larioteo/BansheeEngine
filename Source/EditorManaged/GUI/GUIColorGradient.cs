using System;
using bs;

namespace bs.Editor
{
    partial class GUIColorGradient
    {
        /// <summary>
        /// Callback triggered when the user clicks on the GUI element.
        /// </summary>
        partial void Callback_OnClicked()
        {
            GradientPicker.Show(Gradient, (success, colorGradient) =>
            {
                if (!success)
                    return;

                Gradient = colorGradient;
            });

        }
    }
}
