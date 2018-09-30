using System;
using BansheeEngine;

namespace BansheeEditor
{
    partial class GUIColorDistributionField
    {
        /// <summary>
        /// Triggered when the distribution in the field changes.
        /// </summary>
        public event Action OnChanged;

        partial void OnMinClicked()
        {
            ColorDistribution distribution = Value;

            if (distribution.DistributionType == PropertyDistributionType.Constant ||
                distribution.DistributionType == PropertyDistributionType.RandomRange)
            {
                ColorPicker.Show(distribution.GetMinConstant(), (success, value) =>
                {
                    if (!success)
                        return;

                    if (distribution.DistributionType == PropertyDistributionType.Constant)
                        Value = new ColorDistribution(value);
                    else
                        Value = new ColorDistribution(value, distribution.GetMaxConstant());

                    OnChanged?.Invoke();
                });
            }
            else if (distribution.DistributionType == PropertyDistributionType.Curve || 
                     distribution.DistributionType == PropertyDistributionType.RandomCurveRange)
            {
                GradientPicker.Show(distribution.GetMinGradient(), (success, colorGradient) =>
                {
                    if (!success)
                        return;

                    if(distribution.DistributionType == PropertyDistributionType.Curve)
                        Value = new ColorDistribution(colorGradient);
                    else
                        Value = new ColorDistribution(colorGradient, distribution.GetMaxGradient());

                    OnChanged?.Invoke();
                });
            }
        }

        partial void OnMaxClicked()
        {
            ColorDistribution distribution = Value;

            if (distribution.DistributionType == PropertyDistributionType.RandomRange)
            {
                ColorPicker.Show(distribution.GetMaxConstant(), (success, value) =>
                {
                    if (!success)
                        return;

                    Value = new ColorDistribution(distribution.GetMinConstant(), value);
                    OnChanged?.Invoke();
                });
            }
            else if (distribution.DistributionType == PropertyDistributionType.RandomCurveRange)
            {
                GradientPicker.Show(distribution.GetMaxGradient(), (success, colorGradient) =>
                {
                    if (!success)
                        return;

                    Value = new ColorDistribution(distribution.GetMinGradient(), colorGradient);
                    OnChanged?.Invoke();
                });
            }
        }
    }
}
