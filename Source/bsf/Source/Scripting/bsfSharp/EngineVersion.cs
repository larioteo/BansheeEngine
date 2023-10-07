// Autogenerated file, please do not edit!

using System;

namespace bs
{
    /// <summary>
    /// Provides version information about the engine/editor.
    /// </summary>
    public static class EngineVersion
    {
        /// <summary>
        /// Returns the version of the engine as a text in MAJOR.MINOR.PATCH format.
        /// </summary>
        public static string GetFullVersionString()
        {
            return verMajor.ToString() + "." + verMinor.ToString() + "." + verPatch.ToString();
        }
        public static int GetMajorVersionNumber() { return verMajor; }
        public static int GetMinorVersionNumber() { return verMinor; }
        public static int GetPatchVersionNumber() { return verPatch; }
        public static int GetCurrentReleaseYearNumber() { return currRelYear; }

        private const int verMajor = 0;
        private const int verMinor = 5;
        private const int verPatch = 0;
        private const int currRelYear = 2019;
    }
}