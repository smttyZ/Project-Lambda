#pragma once
namespace lambda::core {

// Primary template declaration
template<typename T>
struct TypeLimits;

template<>
struct TypeLimits<double> {
    // This specialization exists (not the generic fallback)
    static constexpr bool is_specialized = true;

    // --- Fundamental binary properties ---
    static constexpr bool is_signed   = true;
    static constexpr bool is_integer  = false;
    static constexpr bool is_exact    = false;
    static constexpr int  radix       = 2;          // base-2 (IEEE 754)

    // --- Precision & representation ---
    static constexpr int  digits       = 53;        // number of binary digits in mantissa
    static constexpr int  digits10     = 15;        // decimal digits of precision
    static constexpr int  max_digits10 = 17;        // digits needed to uniquely represent any value

    // --- Range values ---
    static constexpr double MIN = 2.2250738585072014e-308;  // smallest normalized positive value
    static constexpr double MAX = 1.7976931348623157e+308;  // largest finite value
    static constexpr double EPSILON = 2.2204460492503131e-16; // difference between 1.0 and next representable value

    // --- Exponent limits ---
    static constexpr int min_exponent   = -1021;
    static constexpr int min_exponent10 = -307;
    static constexpr int max_exponent   = 1024;
    static constexpr int max_exponent10 = 308;

    // --- IEEE 754 features ---
    static constexpr bool has_infinity       = true;
    static constexpr bool has_quiet_NaN      = true;
    static constexpr bool has_signaling_NaN  = true;
    static constexpr bool is_iec559          = true;  // confirms IEEE 754 compliance
    static constexpr bool is_bounded         = true;
    static constexpr bool is_modulo          = false;

    // --- Rounding & behavior ---
    enum class FloatRoundStyle {
        Indeterminate = -1,
        TowardZero = 0,
        ToNearest = 1,
        TowardInfinity = 2,
        TowardNegInfinity = 3
    };
    static constexpr FloatRoundStyle round_style = FloatRoundStyle::ToNearest;

    // --- Functional equivalents ---
    static constexpr double min() noexcept { return MIN; }
    static constexpr double max() noexcept { return MAX; }
    static constexpr double epsilon() noexcept { return EPSILON; }
    static constexpr double lowest() noexcept { return -MAX; }
};

// Specialization for float
template<>
struct TypeLimits<float> {
    static constexpr bool is_specialized = true;

    // --- Fundamental binary properties ---
    static constexpr bool is_signed   = true;
    static constexpr bool is_integer  = false;
    static constexpr bool is_exact    = false;
    static constexpr int  radix       = 2;

    // --- Precision & representation ---
    static constexpr int  digits       = 24;
    static constexpr int  digits10     = 6;
    static constexpr int  max_digits10 = 9;

    // --- Range values ---
    static constexpr float MIN = 1.175494351e-38F;
    static constexpr float MAX = 3.402823466e+38F;
    static constexpr float EPSILON = 1.192092896e-07F;

    // --- Exponent limits ---
    static constexpr int min_exponent   = -125;
    static constexpr int min_exponent10 = -37;
    static constexpr int max_exponent   = 128;
    static constexpr int max_exponent10 = 38;

    // --- IEEE 754 features ---
    static constexpr bool has_infinity       = true;
    static constexpr bool has_quiet_NaN      = true;
    static constexpr bool has_signaling_NaN  = true;
    static constexpr bool is_iec559          = true;
    static constexpr bool is_bounded         = true;
    static constexpr bool is_modulo          = false;

    // --- Rounding & behavior ---
    using FloatRoundStyle = TypeLimits<double>::FloatRoundStyle;
    static constexpr FloatRoundStyle round_style = FloatRoundStyle::ToNearest;

    // --- Functional equivalents ---
    static constexpr float min() noexcept { return MIN; }
    static constexpr float max() noexcept { return MAX; }
    static constexpr float epsilon() noexcept { return EPSILON; }
    static constexpr float lowest() noexcept { return -MAX; }
};

// Specialization for long double
template<>
struct TypeLimits<long double> {
    static constexpr bool is_specialized = true;

    // --- Fundamental binary properties ---
    static constexpr bool is_signed   = true;
    static constexpr bool is_integer  = false;
    static constexpr bool is_exact    = false;
    static constexpr int  radix       = 2;

    // --- Precision & representation ---
    static constexpr int  digits       = 64;
    static constexpr int  digits10     = 18;
    static constexpr int  max_digits10 = 21;

    // --- Range values ---
    static constexpr long double MIN = 3.3621031431120935e-4932L;
    static constexpr long double MAX = 1.189731495357231765e+4932L;
    static constexpr long double EPSILON = 1.084202172485504434e-19L;

    // --- Exponent limits ---
    static constexpr int min_exponent   = -16381;
    static constexpr int min_exponent10 = -4931;
    static constexpr int max_exponent   = 16384;
    static constexpr int max_exponent10 = 4932;

    // --- IEEE 754 features ---
    static constexpr bool has_infinity       = true;
    static constexpr bool has_quiet_NaN      = true;
    static constexpr bool has_signaling_NaN  = true;
    static constexpr bool is_iec559          = true;
    static constexpr bool is_bounded         = true;
    static constexpr bool is_modulo          = false;

    // --- Rounding & behavior ---
    using FloatRoundStyle = TypeLimits<double>::FloatRoundStyle;
    static constexpr FloatRoundStyle round_style = FloatRoundStyle::ToNearest;

    // --- Functional equivalents ---
    static constexpr long double min() noexcept { return MIN; }
    static constexpr long double max() noexcept { return MAX; }
    static constexpr long double epsilon() noexcept { return EPSILON; }
    static constexpr long double lowest() noexcept { return -MAX; }
};

// Specialization for bool
template<>
struct TypeLimits<bool> {
    static constexpr bool is_specialized = true;

    // --- Fundamental binary properties ---
    static constexpr bool is_signed   = false;
    static constexpr bool is_integer  = true;
    static constexpr bool is_exact    = true;
    static constexpr int  radix       = 2;

    // --- Precision & representation ---
    static constexpr int  digits       = 1;
    static constexpr int  digits10     = 0;
    static constexpr int  max_digits10 = 1;

    // --- Range values ---
    static constexpr bool MIN = false;
    static constexpr bool MAX = true;
    static constexpr int EPSILON = 0;

    // --- Exponent limits ---
    static constexpr int min_exponent   = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int max_exponent   = 0;
    static constexpr int max_exponent10 = 0;

    // --- Features ---
    static constexpr bool has_infinity       = false;
    static constexpr bool has_quiet_NaN      = false;
    static constexpr bool has_signaling_NaN  = false;
    static constexpr bool is_iec559          = false;
    static constexpr bool is_bounded         = true;
    static constexpr bool is_modulo          = false;

    // --- Rounding & behavior ---
    enum class FloatRoundStyle {
        Indeterminate = -1,
        TowardZero = 0
    };
    static constexpr FloatRoundStyle round_style = FloatRoundStyle::TowardZero;

    // --- Functional equivalents ---
    static constexpr bool min() noexcept { return MIN; }
    static constexpr bool max() noexcept { return MAX; }
    static constexpr int epsilon() noexcept { return EPSILON; }
    static constexpr bool lowest() noexcept { return MIN; }
};

} // namespace lambda::core