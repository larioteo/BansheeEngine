using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUIColorGradient
    {
        /// <summary>
        /// Callback triggered when the user clicks on the GUI element.
        /// </summary>
        partial void OnClicked()
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
