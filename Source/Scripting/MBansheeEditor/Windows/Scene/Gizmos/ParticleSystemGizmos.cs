//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2017 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Gizmos
     *  @{
     */

    /// <summary>
    /// Handles drawing of gizmos and selection callback for the <see cref="ParticleSystem"/> component.
    /// </summary>
    internal class ParticleSystemGizmos
    {
        /// <summary>
        /// Method called by the runtime when gizmos are meant to be drawn.
        /// </summary>
        /// <param name="component">Component to draw gizmos for.</param>
        [DrawGizmo(DrawGizmoFlags.Selected)]
        private static void Draw(ParticleSystem component)
        {
            SceneObject so = component.SceneObject;

            Gizmos.Color = Color.Yellow;
            Gizmos.Transform = Matrix4.TRS(so.Position, Quaternion.LookRotation(so.Rotation.Forward, so.Rotation.Up), Vector3.One);

            // TODO
        }

        /// <summary>
        /// Method called by the runtime when the component is selected or deselected.
        /// </summary>
        /// <param name="component">Component that was selected or deselected.</param>
        /// <param name="selected">If true the provided component was selected, otherwise deselected.</param>
        [OnSelectionChanged]
        private static void SelectionChanged(ParticleSystem component, bool selected)
        {
            component.TogglePreviewMode(selected);
        }
    }

    /** @} */
}
