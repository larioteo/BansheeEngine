//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//

using System;
using System.Collections.Generic;
using bs;

namespace bs.Editor
{
    /** @addtogroup Inspectors
     *  @{
     */

    /// <summary>
    /// Renders an inspector for the <see cref="Material"/> resource.
    /// </summary>
    [CustomInspector(typeof (Material))]
    internal class MaterialInspector : Inspector
    {
        private MaterialParamGUI[] guiParams;
        private GUIResourceField shaderField;
        private GUIEnumField builtinShaderField;

        /// <inheritdoc/>
        protected internal override void Initialize()
        {
            LoadResource();

            Material material = InspectedObject as Material;
            if (material == null)
                return;

            Shader activeShader = material.Shader.Value;
            BuiltinShader builtinType = ShaderToBuiltin(activeShader);

            builtinShaderField = new GUIEnumField(typeof(BuiltinShader), new LocEdString("Shader"));
            builtinShaderField.Value = (ulong) builtinType;
            builtinShaderField.OnSelectionChanged += x =>
            {
                BuiltinShader newBuiltinType = (BuiltinShader) x;

                material.Shader = Builtin.GetShader(newBuiltinType);
                EditorApplication.SetDirty(material);
                RebuildParamGUI(material);

                bool newIsCustom = newBuiltinType == BuiltinShader.Custom;
                shaderField.Active = newIsCustom;
            };

            shaderField = new GUIResourceField(typeof(Shader), new LocEdString("Shader file"));
            shaderField.ValueRef = material.Shader;
            shaderField.OnChanged += (x) =>
            {
                Shader shader = Resources.Load<Shader>(x.UUID);

                material.Shader = shader;
                EditorApplication.SetDirty(material);
                RebuildParamGUI(material);
            };

            bool isCustom = builtinType == BuiltinShader.Custom;
            shaderField.Active = isCustom;

            RebuildParamGUI(material);
        }

        /// <inheritdoc/>
        protected internal override InspectableState Refresh()
        {
            Material material = InspectedObject as Material;
            if (material == null)
                return InspectableState.NotModified;

            if (material.Shader != shaderField.ValueRef)
            {
                shaderField.ValueRef = material.Shader;
                RebuildParamGUI(material);
            }

            if (guiParams != null)
            {
                foreach (var param in guiParams)
                    param.Refresh(material);
            }

            return InspectableState.NotModified;
        }

        /// <summary>
        /// Recreates GUI elements for all material parameters.
        /// </summary>
        /// <param name="material">Material to create parameters for</param>
        private void RebuildParamGUI(Material material)
        {
            if (guiParams != null)
            {
                foreach (var param in guiParams)
                    param.Destroy();

                guiParams = null;
            }

            Layout.Clear();
            Layout.AddElement(builtinShaderField);
            Layout.AddElement(shaderField);

            if (material != null && material.Shader != null)
                guiParams = CreateMaterialGUI(material, Layout);
        }

        /// <summary>
        /// Converts a shader resource into a builtin shader.
        /// </summary>
        /// <param name="shader">Shader resource to convert.</param>
        /// <returns>Type of builtin shader, if any.</returns>
        private BuiltinShader ShaderToBuiltin(Shader shader)
        {
            // Note: Might be nice to have a better way to detect the builtin shader perhaps (store it in Material?)
            //   - Or I could just compare UUID's here to avoid loading the shaders
            var enumValues = Enum.GetValues(typeof(BuiltinShader));
            for (int i = 1; i < enumValues.Length; i++)
            {
                Shader builtinShader = Builtin.GetShader((BuiltinShader) i);
                if (builtinShader == shader)
                    return (BuiltinShader) i;
            }
            
            return BuiltinShader.Custom;
        }

        /// <summary>
        /// Creates a set of objects in which each object represents a GUI for a material parameter.
        /// </summary>
        /// <param name="mat">Material for whose parameters to create GUI for.</param>
        /// <param name="layout">Layout to add the parameter GUI elements to.</param>
        /// <returns>A material parameter GUI object for each supported material parameter.</returns>
        static internal MaterialParamGUI[] CreateMaterialGUI(Material mat, GUILayout layout)
        {
            Shader shader = mat.Shader.Value;
            if (shader == null)
                return new MaterialParamGUI[0];

            List<MaterialParamGUI> guiParams = new List<MaterialParamGUI>();
            ShaderParameter[] shaderParams = shader.Parameters;

            foreach (var param in shaderParams)
            {
                if (param.isInternal)
                    continue;

                switch (param.type)
                {
                    case ShaderParameterType.Float:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamFloatGUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Vector2:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamVec2GUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Vector3:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamVec3GUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Vector4:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamVec4GUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Matrix3:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamMat3GUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Matrix4:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamMat4GUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Color:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamColorGUI(param, mat, layout));
                        break;
                    case ShaderParameterType.Texture2D:
                    case ShaderParameterType.Texture3D:
                    case ShaderParameterType.TextureCube:
                        layout.AddSpace(5);
                        guiParams.Add(new MaterialParamTextureGUI(param, mat, layout));
                        break;
                }
            }

            return guiParams.ToArray();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single parameter in a <see cref="Material"/>.
    /// </summary>
    internal abstract class MaterialParamGUI
    {
        protected ShaderParameter shaderParam;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for.</param>
        protected MaterialParamGUI(ShaderParameter shaderParam)
        {
            this.shaderParam = shaderParam;
        }

        /// <summary>
        /// Checks if the data stored in GUI and in the material matches, and updates the GUI if it doesn't.
        /// </summary>
        /// <param name="material">Material whose data to check.</param>
        internal abstract void Refresh(Material material);

        /// <summary> 
        /// Destroys the internal GUI elements.
        /// </summary>
        internal abstract void Destroy();
    }

    /// <summary>
    /// Contains GUI element(s) for a single floating point parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamFloatGUI : MaterialParamGUI
    {
        private GUILayout fieldLayout;
        private GUIFloatField guiConstant;
        private GUICurvesField guiCurves;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of floating point type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamFloatGUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);

            var guiToggle = new GUIToggle(new GUIContent(
                EditorBuiltin.GetEditorToggleIcon(EditorToggleIcon.AnimateProperty), new LocString("Animate")));
            guiConstant = new GUIFloatField(title);
            guiCurves = new GUICurvesField(title);

            bool isAnimated = material.IsAnimated(shaderParam.name);
            guiConstant.Active = !isAnimated;
            guiCurves.Active = isAnimated;

            fieldLayout = layout.AddLayoutX();
            fieldLayout.AddElement(guiConstant);
            fieldLayout.AddElement(guiCurves);
            fieldLayout.AddSpace(10);
            fieldLayout.AddElement(guiToggle);

            guiConstant.OnChanged += (x) =>
            {
                material.SetFloat(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            guiCurves.OnChanged += x =>
            {
                material.SetFloatCurve(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            guiToggle.OnToggled += x =>
            {
                guiConstant.Active = !x;
                guiCurves.Active = x;
            };
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            bool isAnimated = material.IsAnimated(shaderParam.name);
            if (isAnimated)
                guiCurves.SetCurve(material.GetFloatCurve(shaderParam.name));
            else
                guiConstant.Value = material.GetFloat(shaderParam.name);
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            fieldLayout.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single 2D vector parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamVec2GUI : MaterialParamGUI
    {
        private GUIVector2Field guiElem;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of 2D vector type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamVec2GUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);
            guiElem = new GUIVector2Field(title);
            guiElem.OnChanged += (x) =>
            {
                material.SetVector2(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            layout.AddElement(guiElem);
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            guiElem.Value = material.GetVector2(shaderParam.name);
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            guiElem.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single 3D vector parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamVec3GUI : MaterialParamGUI
    {
        private GUIVector3Field guiElem;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of 3D vector type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamVec3GUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);
            guiElem = new GUIVector3Field(title);
            guiElem.OnChanged += (x) =>
            {
                material.SetVector3(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            layout.AddElement(guiElem);
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            guiElem.Value = material.GetVector3(shaderParam.name);
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            guiElem.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single 4D vector parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamVec4GUI : MaterialParamGUI
    {
        private GUIVector4Field guiElem;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of 4D vector type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamVec4GUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);
            guiElem = new GUIVector4Field(title);
            guiElem.OnChanged += (x) =>
            {
                material.SetVector4(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            layout.AddElement(guiElem);
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            guiElem.Value = material.GetVector4(shaderParam.name);
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            guiElem.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single 3x3 matrix parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamMat3GUI : MaterialParamGUI
    {
        private const int MAT_SIZE = 3;

        private GUILayout mainLayout;
        private GUIFloatField[] guiMatFields = new GUIFloatField[MAT_SIZE * MAT_SIZE];

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of 3x3 matrix type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamMat3GUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);
            GUILabel guiTitle = new GUILabel(title, GUIOption.FixedWidth(100));

            mainLayout = layout.AddLayoutY();
            GUILayoutX titleLayout = mainLayout.AddLayoutX();
            titleLayout.AddElement(guiTitle);
            titleLayout.AddFlexibleSpace();

            GUILayoutY contentLayout = mainLayout.AddLayoutY();

            GUILayoutX[] rows = new GUILayoutX[MAT_SIZE];
            for (int i = 0; i < rows.Length; i++)
                rows[i] = contentLayout.AddLayoutX();

            for (int row = 0; row < MAT_SIZE; row++)
            {
                for (int col = 0; col < MAT_SIZE; col++)
                {
                    int index = row * MAT_SIZE + col;
                    guiMatFields[index] = new GUIFloatField(row + "," + col, 20, "", GUIOption.FixedWidth(80));

                    GUIFloatField field = guiMatFields[index];
                    rows[row].AddElement(field);
                    rows[row].AddSpace(5);

                    int hoistedRow = row;
                    int hoistedCol = col;
                    field.OnChanged += (x) =>
                    {
                        Matrix3 value = material.GetMatrix3(shaderParam.name);
                        value[hoistedRow, hoistedCol] = x;
                        material.SetMatrix3(shaderParam.name, value);
                        EditorApplication.SetDirty(material);
                    };
                }
            }
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            Matrix3 value = material.GetMatrix3(shaderParam.name);

            for (int row = 0; row < MAT_SIZE; row++)
            {
                for (int col = 0; col < MAT_SIZE; col++)
                {
                    int index = row * MAT_SIZE + col;
                    guiMatFields[index].Value = value[row, col];
                }
            }
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            mainLayout.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single 4x4 matrix parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamMat4GUI : MaterialParamGUI
    {
        private const int MAT_SIZE = 4;

        private GUILayout mainLayout;
        private GUIFloatField[] guiMatFields = new GUIFloatField[MAT_SIZE * MAT_SIZE];

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of 4x4 matrix type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamMat4GUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);
            GUILabel guiTitle = new GUILabel(title, GUIOption.FixedWidth(100));

            mainLayout = layout.AddLayoutY();
            GUILayoutX titleLayout = mainLayout.AddLayoutX();
            titleLayout.AddElement(guiTitle);
            titleLayout.AddFlexibleSpace();

            GUILayoutY contentLayout = mainLayout.AddLayoutY();

            GUILayoutX[] rows = new GUILayoutX[MAT_SIZE];
            for (int i = 0; i < rows.Length; i++)
                rows[i] = contentLayout.AddLayoutX();

            for (int row = 0; row < MAT_SIZE; row++)
            {
                for (int col = 0; col < MAT_SIZE; col++)
                {
                    int index = row * MAT_SIZE + col;
                    guiMatFields[index] = new GUIFloatField(row + "," + col, 20, "", GUIOption.FixedWidth(80));

                    GUIFloatField field = guiMatFields[index];
                    rows[row].AddElement(field);
                    rows[row].AddSpace(5);

                    int hoistedRow = row;
                    int hoistedCol = col;
                    field.OnChanged += (x) =>
                    {
                        Matrix4 value = material.GetMatrix4(shaderParam.name);
                        value[hoistedRow, hoistedCol] = x;
                        material.SetMatrix4(shaderParam.name, value);
                        EditorApplication.SetDirty(material);
                    };
                }
            }
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            Matrix4 value = material.GetMatrix4(shaderParam.name);

            for (int row = 0; row < MAT_SIZE; row++)
            {
                for (int col = 0; col < MAT_SIZE; col++)
                {
                    int index = row * MAT_SIZE + col;
                    guiMatFields[index].Value = value[row, col];
                }
            }
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            mainLayout.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single color parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamColorGUI : MaterialParamGUI
    {
        private GUILayout fieldLayout;
        private GUIColorField guiColor;
        private GUIColorGradientField guiColorGradient;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of color type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamColorGUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);

            var guiToggle = new GUIToggle(new GUIContent( 
                EditorBuiltin.GetEditorToggleIcon(EditorToggleIcon.AnimateProperty), new LocString("Animate")));
            guiColor = new GUIColorField(title);
            guiColorGradient = new GUIColorGradientField(title);

            bool isAnimated = material.IsAnimated(shaderParam.name);
            guiColor.Active = !isAnimated;
            guiColorGradient.Active = isAnimated;

            fieldLayout = layout.AddLayoutX();
            fieldLayout.AddElement(guiColor);
            fieldLayout.AddElement(guiColorGradient);
            fieldLayout.AddSpace(10);
            fieldLayout.AddElement(guiToggle);

            guiColor.OnChanged += (x) =>
            {
                material.SetColor(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            guiColorGradient.OnChanged += x =>
            {
                material.SetColorGradient(shaderParam.name, x);
                EditorApplication.SetDirty(material);
            };

            guiToggle.OnToggled += x =>
            {
                guiColor.Active = !x;
                guiColorGradient.Active = x;

                if (x)
                {
                    ColorGradient gradient = material.GetColorGradient(shaderParam.name);
                    if (gradient.NumKeys == 0)
                        material.SetColorGradient(shaderParam.name, new ColorGradient(material.GetColor(shaderParam.name)));
                }
            };
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            bool isAnimated = material.IsAnimated(shaderParam.name);
            if (isAnimated)
                guiColorGradient.Value = material.GetColorGradient(shaderParam.name);
            else
                guiColor.Value = material.GetColor(shaderParam.name);
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            fieldLayout.Destroy();
        }
    }

    /// <summary>
    /// Contains GUI element(s) for a single texture parameter in a <see cref="Material"/>.
    /// </summary>
    internal class MaterialParamTextureGUI : MaterialParamGUI
    {
        private GUITextureField guiElem;

        /// <summary>
        /// Creates a new material parameter GUI.
        /// </summary>
        /// <param name="shaderParam">Shader parameter to create the GUI for. Must be of texture type.</param>
        /// <param name="material">Material the parameter is a part of.</param>
        /// <param name="layout">Layout to append the GUI elements to.</param>
        internal MaterialParamTextureGUI(ShaderParameter shaderParam, Material material, GUILayout layout)
            : base(shaderParam)
        {
            LocString title = new LocEdString(shaderParam.name);

            GUITextureFieldType type = shaderParam.type == ShaderParameterType.Texture2D ? 
                GUITextureFieldType.TextureOrSpriteTexture :
                GUITextureFieldType.Texture;

            guiElem = new GUITextureField(type, title);

            switch (shaderParam.type)
            {
                case ShaderParameterType.Texture2D:
                case ShaderParameterType.Texture3D:
                case ShaderParameterType.TextureCube:
                    guiElem.OnChanged += (x) =>
                    {
                        string path = ProjectLibrary.GetPath(x.UUID);
                        if (!string.IsNullOrEmpty(path))
                        {
                            if (ProjectLibrary.GetEntry(path) is FileEntry fileEntry)
                            {
                                if (fileEntry.ResourceMetas.Length > 0)
                                {
                                    ResourceMeta meta = fileEntry.ResourceMetas[0];
                                    if (meta.ResType == ResourceType.SpriteTexture)
                                        material.SetSpriteTexture(shaderParam.name, x.As<SpriteTexture>());
                                    else if(meta.ResType == ResourceType.Texture)
                                        material.SetTexture(shaderParam.name, x.As<Texture>());
                                }
                            }
                        }
                        else
                            material.SetTexture(shaderParam.name, null);

                        EditorApplication.SetDirty(material);
                    };
                    break;
            }

            layout.AddElement(guiElem);
        }

        /// <inheritdoc/>
        internal override void Refresh(Material material)
        {
            RRef<Texture> texture;
            switch (shaderParam.type)
            {
                case ShaderParameterType.Texture2D:
                    RRef<SpriteTexture> spriteTex = material.GetSpriteTexture(shaderParam.name);

                    if (spriteTex != null && spriteTex.UUID != UUID.Empty)
                        guiElem.SpriteTextureRef = spriteTex;
                    else
                    {
                        texture = material.GetTexture(shaderParam.name);
                        guiElem.TextureRef = texture;
                    }

                    break;
                case ShaderParameterType.Texture3D:
                case ShaderParameterType.TextureCube:
                    texture = material.GetTexture(shaderParam.name);
                    guiElem.TextureRef = texture;
                    break;
            }
        }

        /// <inheritdoc/>
        internal override void Destroy()
        {
            guiElem.Destroy();
        }
    }

    /** @} */
}
