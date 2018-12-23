//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;

namespace BansheeEditor
{
    /// <summary>
    /// Contains boolean information about a field style.
    /// </summary>
    [Flags]
    public enum InspectableFieldStyleFlags
    {
        None          = 0,

        /// <summary>
        /// Floating point field should be represented as a slider rather than a plain input field.
        /// </summary>
        UseSlider     = 1 << 0,

        /// <summary>
        /// Integer field should be represented as a layer mask drop down instead of a plain integer input field.
        /// </summary>
        UseLayerMask  = 1 << 1,

        /// <summary>
        /// Object accessed by the inspectable field is passed as a copy. This means modifications to the object returned by
        /// the property getter will not be registered until the object is re-assigned to the property. Similarly,
        /// modifications to the object passed to the setter, after the setter has been called, will not be registered by
        /// the field. Only relevant if a field type is a reference type.
        /// </summary>
        CopiedAsValue = 1 << 2,

        /// <summary>
        /// Object returned by the inspectable field will never be null, and null should never be passed to the field. Only
        /// relevant if a field type is a reference type.
        /// </summary>
        NotNull       = 1 << 3,

        /// <summary>
        /// Field represents a property that wraps a native object. Getters and setters of such a property issue calls into
        /// native code to update the native object.
        /// </summary>
        NativeWrapper = 1 << 4,

        /// <summary>
        /// When a field changes those changes need to be applied to the parent object by calling the field setter. Only
        /// applicable to properties containing reference types.
        /// </summary>
        ApplyOnDirty = 1 << 5
    }

    /// <summary>
    /// Contains all the information about a field style.
    /// </summary>
    public class InspectableFieldStyleInfo
    {
        /// <summary>
        /// Information about the field range.
        /// </summary>
        public InspectableFieldRangeStyle RangeStyle;

        /// <summary>
        /// Information about the field stepping.
        /// </summary>
        public InspectableFieldStepStyle StepStyle;

        /// <summary>
        /// Boolean information about the field.
        /// </summary>
        public InspectableFieldStyleFlags StyleFlags;

        /// <summary>
        /// Creates an empty set of information about a field style.
        /// </summary>
        public InspectableFieldStyleInfo()
        {
            
        }

        /// <summary>
        /// Makes a deep copy of this object.
        /// </summary>
        public InspectableFieldStyleInfo Clone()
        {
            InspectableFieldStyleInfo style = new InspectableFieldStyleInfo();
            style.StyleFlags = StyleFlags;

            if(RangeStyle != null)
                style.RangeStyle = new InspectableFieldRangeStyle(RangeStyle.Min, RangeStyle.Max, RangeStyle.Slider);

            if(StepStyle != null)
                style.StepStyle = new InspectableFieldStepStyle(StepStyle.Step);

            return style;
        }
    }
}
