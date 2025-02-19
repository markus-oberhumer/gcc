/* { dg-do run { target { riscv_v } } } */
/* { dg-options "-O2" } */

#include<cmath>
#include<cstddef>
#include<cstdint>
#include<iomanip>
#include<ios>
#include<iostream>
#include<memory>
#include<type_traits>
#include"riscv_vector.h"

using std::addressof;
using std::cerr;
using std::endl;
using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::ptrdiff_t;
using std::size_t;
using float16_t = _Float16;
using float32_t = float;
using float64_t = double;

template<class T, class T2>
constexpr T uint_to_float(T2 val) noexcept
{
  return *reinterpret_cast<T*>(&val);
}

constexpr const auto &f16(uint_to_float<float16_t, uint16_t>);
constexpr const auto &f32(uint_to_float<float32_t, uint32_t>);
constexpr const auto &f64(uint_to_float<float64_t, uint64_t>);

template<class T>
struct To_uint
{
  using type = std::conditional_t<
    sizeof(T) == 1, uint8_t, std::conditional_t<
      sizeof(T) == 2, uint16_t, std::conditional_t<
        sizeof(T) == 4, uint32_t, std::conditional_t<
          sizeof(T) == 8, uint64_t, void
        >
      >
    >
  >;
};

// isnan() does not support half type
template<class T>
struct To_float
{
  using type = std::conditional_t<
    std::is_same<T, float16_t>::value, float, std::conditional_t<
      std::is_same<T, float32_t>::value, float, std::conditional_t<
        std::is_same<T, float64_t>::value, double, float
      >
    >
  >;
};

template<class T>
using To_uint_t = typename To_uint<T>::type;

template<class T>
using To_isnan_float = typename To_float<T>::type;

template <class T>
void print_float(std::ostream &os, T val)
{
  using std::setw;
  os << std::hex << std::setfill('0') << setw(sizeof(T) * 2) << *reinterpret_cast<To_uint_t<T>*>(addressof(val)) << setw(0) << std::dec;
}

template <class T>
bool __attribute__((noinline))
check(const T *a, const T *b, size_t size)
{
  bool rv = true;
  for (size_t i = 0; i < (size / sizeof(T)); ++i) {
    if (reinterpret_cast<const To_uint_t<T> *>(a)[i] ==
        reinterpret_cast<const To_uint_t<T> *>(b)[i])
      continue;
    // floating negative zero == positive zero
    if ((std::is_floating_point_v<T> || std::is_same<T, float16_t>::value) &&
        (a[i] == b[i]))
      continue;
    // if both result are NaN, return true
    if ((std::is_same<T, float16_t>::value || std::is_floating_point_v<T>) &&
         std::isnan(static_cast<To_isnan_float<T>>(a[i])) &&
         std::isnan(static_cast<To_isnan_float<T>>(b[i])))
      continue;

    if (std::is_same<T, float16_t>::value) {
      cerr << std::hex << std::setfill('0') << std::setw(sizeof(T) * 2) << "["
           << i
           << "] result/golden:" << reinterpret_cast<const To_uint_t<T> *>(a)[i]
           << " != " << reinterpret_cast<const To_uint_t<T> *>(b)[i]
           << std::setw(0) << std::dec << endl;
    } else if constexpr (std::is_floating_point_v<T>) {
      cerr << "[" << i << "] result/golden:" << a[i] << "(";
      print_float(cerr, a[i]);
      cerr << ") != " << b[i] << "(";
      print_float(cerr, b[i]);
      cerr << ")" << endl;
    } else if constexpr (std::is_unsigned_v<T>) {
      cerr << "[" << i << "] result/golden: " << static_cast<uintmax_t>(a[i])
           << " != " << static_cast<uintmax_t>(b[i]) << endl;
    } else {
      cerr << "[" << i << "] result/golden:" << static_cast<intmax_t>(a[i])
           << " != " << static_cast<intmax_t>(b[i]) << endl;
    }
    rv = false;
  }
  return rv;
}

template <class T>
bool __attribute__((noinline))
check(const T a, const T golden)
{
  return check(addressof(a), addressof(golden), sizeof(T));
}



int main()
{
int return_value = 0;

size_t var_128 = 120u;
uint64_t var_127 [] = {10247815139382195571u, 7553514226738151656u, 8137034001984249717u, 1830988008579804275u, 12485891889796475883u, 3736113326113888510u, 711898336935905414u, 1766420694477792245u, 2953671709036220187u, 5512330794907312127u, 7952990648142234505u, 13869584398819855770u, 2408717139903002058u, 11092170387738276891u, 18397020437758593652u};
size_t var_125 = 56u;
uint64_t var_124 [] = {17406140965283708416u, 7763514595608731964u, 16115534765690077835u, 11231660409811348566u, 15524877149379504932u, 18332759340072606684u, 13061196588776176296u};
size_t var_122 = 88u;
uint64_t var_121 [] = {6707184356131601529u, 3297729015471999648u, 8061866611138600782u, 8800452268050799000u, 15020615771672721108u, 641196928272078212u, 11085175814396974197u, 11837733385127913629u, 15049864486786069233u, 11168326475583966677u, 17247135944700039313u};
size_t var_119 = 8u;
uint64_t var_118 [] = {18331694445854200932u};
size_t var_116 = 8u;
uint64_t var_115 [] = {10064759157889306246u};
size_t var_113 = 8u;
uint64_t var_112 [] = {5614222760803579557u};
size_t var_110 = 8u;
uint64_t var_109 [] = {10005960522681245691u};
size_t var_107 = 8u;
uint64_t var_106 [] = {1475954422756504086u};
size_t var_104 = 40u;
uint64_t var_103 [] = {6626590334479776340u, 2241199338160557252u, 16060726272050137143u, 17732233298880458138u, 7263785864330966034u};
size_t var_101 = 8u;
uint64_t var_100 [] = {7345263286500344069u};
size_t var_98 = 56u;
uint64_t var_97 [] = {5956735885135481938u, 4182044049298386488u, 7623452711169899944u, 14068300089985942305u, 11493693468971232432u, 7345263286500344069u, 346416287130549105u};
ptrdiff_t var_95 = 8;
uint64_t var_94 [] = {12414305289291450974u, 16538359851375302352u, 8313132055691416560u, 13867065269079349521u, 1017808771721427764u, 17356330368822779652u, 3290756935902994118u};
ptrdiff_t var_93 = 0;
uint64_t var_92 [] = {10799832758926747660u};
ptrdiff_t var_91 = 8;
uint64_t var_90 [] = {13805165872561632310u, 774068163429852672u, 17064778312135541796u, 6875624645824733541u, 423214091817222295u};
ptrdiff_t var_89 = 0;
uint64_t var_88 [] = {14010031310442528161u};
ptrdiff_t var_87 = 0;
uint64_t var_86 [] = {7356817956819184451u};
ptrdiff_t var_85 = 16;
uint64_t var_84 [] = {947422547004695300u};
ptrdiff_t var_83 = 0;
uint64_t var_82 [] = {6235535364195587831u};
ptrdiff_t var_81 = 0;
uint64_t var_80 [] = {15193925570144736210u};
ptrdiff_t var_79 = 16;
uint64_t var_78 [] = {533640416774363423u, 3297729015471999648u, 8489938588667541712u, 8800452268050799000u, 17666107708045901194u, 641196928272078212u, 7559177638472102726u, 11837733385127913629u, 5680384540848464675u, 11168326475583966677u, 3255398313722498431u};
ptrdiff_t var_77 = 16;
uint64_t var_76 [] = {12533337824753551080u, 7763514595608731964u, 13795692181151647051u, 11231660409811348566u, 250297762503526787u, 18332759340072606684u, 16140613718861239193u};
ptrdiff_t var_75 = 16;
uint64_t var_74 [] = {7538716940910148046u, 7553514226738151656u, 157158663635958630u, 1830988008579804275u, 7114448579865347051u, 3736113326113888510u, 15309920862503524726u, 1766420694477792245u, 14456186678097064011u, 5512330794907312127u, 2571987622086860087u, 13869584398819855770u, 4551693039826462697u, 11092170387738276891u, 18400979329953061252u};
uint64_t var_73 [] = {531390701392661486u, 14191860546689599459u, 6397974831436088037u, 6061287482776831231u, 11824792493993797371u, 12986570522226503009u, 2021643368358337136u};
uint64_t var_72 [] = {17955355009468457553u, 14703297809170010498u, 7622994535709940528u, 9446060281158572795u, 17265810070545762724u, 8550158278057152140u, 4740186099373236988u};
int32_t var_71 [] = {-844681533, 430047046, -1582399717, -1395793554, -1957933974, 1861214609, -778122672};
uint64_t var_70 [] = {10247815139382195571u, 8137034001984249717u, 12485891889796475883u, 711898336935905414u, 2953671709036220187u, 7952990648142234505u, 2408717139903002058u, 18397020437758593652u};
uint64_t var_69 [] = {17406140965283708416u, 16115534765690077835u, 15524877149379504932u, 13061196588776176296u};
uint64_t var_68 [] = {6707184356131601529u, 8061866611138600782u, 15020615771672721108u, 11085175814396974197u, 15049864486786069233u, 17247135944700039313u};
uint64_t var_67 [] = {16090077958295291976u, 5058025570064596806u, 18331694445854200932u};
uint64_t var_66 [] = {9277904776365247519u, 6199737835434958138u, 16283102520881457795u, 11745254990704327140u, 10064759157889306246u};
uint64_t var_65 [] = {5614222760803579557u};
uint32_t var_64 [] = {1227690475u, 1502107102u, 801010141u, 2126338631u, 3025649616u, 3487614245u, 14569746u};
float32_t var_63 [] = {f32(2245967112u), f32(2051163058u), f32(3908244833u), f32(3962722910u), f32(111404444u), f32(2790391727u), f32(2300257459u)};
// -2.0946218785136287e-35, 2.521696536530322e+35, -9.183435412395947e+24, -8.624621714752208e+26, 6.165116599290094e-35, -7.285795718059635e-16, -1.8674702225979434e-33

float32_t var_62 [] = {f32(3938692238u), f32(2212435144u), f32(589281906u), f32(2509035433u), f32(1942403032u), f32(3291053766u), f32(1475222084u)};
// -1.1827770064878237e+26, -1.3111533152679839e-36, 8.658888601896916e-18, -5.688580141840109e-26, 3.1488146125197364e+31, -677.9808349609375, 523593154822144.0

int16_t var_61 [] = {-1663, 11444, -8810, 17993, -9281, 3460, -32008};
int8_t var_60 [] = {-31, -84, -128, 97, -3, -22, 77};
uint8_t var_59 [] = {38u, 115u, 20u, 210u, 239u, 182u, 119u};
uint64_t var_58 [] = {16700153237887578248u, 5031037798225230451u, 5292105904994248007u, 191847662260362543u, 17224332114616326956u, 10438953222179951407u, 3274250116478307575u};
uint64_t var_57 [] = {5033313200475315879u, 11361079409953223615u, 7140048274794104683u, 2981932693915571701u, 9476848135713847987u, 12261119440308053562u, 9970426093577270632u};
uint64_t var_56 [] = {2905331234579431349u, 7092114374123614934u, 10005960522681245691u};
uint64_t var_55 [] = {6906626707180673736u, 1475954422756504086u};
int16_t var_54 [] = {3175, 29167, -27933, 26903};
uint64_t var_53 [] = {11254251074008699435u, 5204823814932142037u, 8646232476803655494u, 15091079855619697854u, 12516473234604987981u, 1630341543898427294u, 1369196052764304654u};
int64_t var_52 [] = {2989185173643568993, -1007222647130467543, 9035883417988087253, 356697895597171625, -688843516243652996, 8367631197042162633, 7921162693062268499};
uint64_t var_51 [] = {6626590334479776340u, 2241199338160557252u, 16060726272050137143u, 17732233298880458138u, 7263785864330966034u};
uint64_t var_50 [] = {4933956119501726389u, 6288763602173540886u, 5410560154821202561u, 17226305573183414225u, 7665224654860515905u, 6322483520866588520u, 792086670759048161u};
uint32_t var_49 = 3538698156u;
int32_t var_48 = -1974267178;
int64_t var_47 = 8792666392265243067;
__riscv_vsetvl_e64m8(7);
vuint64m8_t var_20 = __riscv_vle64_v_u64m8(var_73, 7);
// 531390701392661486, 14191860546689599459, 6397974831436088037, 6061287482776831231, 11824792493993797371, 12986570522226503009, 2021643368358337136

vuint64m8_t var_21 = __riscv_vle64_v_u64m8(var_72, 7);
// 17955355009468457553, 14703297809170010498, 7622994535709940528, 9446060281158572795, 17265810070545762724, 8550158278057152140, 4740186099373236988

vint32m4_t var_23 = __riscv_vle32_v_i32m4(var_71, 7);
// -844681533, 430047046, -1582399717, -1395793554, -1957933974, 1861214609, -778122672

__riscv_vsetvl_e64m4(8);
vuint64m4_t var_24 = __riscv_vle64_v_u64m4(var_70, 8);
// 10247815139382195571, 8137034001984249717, 12485891889796475883, 711898336935905414, 2953671709036220187, 7952990648142234505, 2408717139903002058, 18397020437758593652

__riscv_vsetvl_e64m4(4);
vuint64m4_t var_25 = __riscv_vle64_v_u64m4(var_69, 4);
// 17406140965283708416, 16115534765690077835, 15524877149379504932, 13061196588776176296

__riscv_vsetvl_e64m4(6);
vuint64m4_t var_26 = __riscv_vle64_v_u64m4(var_68, 6);
// 6707184356131601529, 8061866611138600782, 15020615771672721108, 11085175814396974197, 15049864486786069233, 17247135944700039313

__riscv_vsetvl_e64m4(3);
vuint64m4_t var_27 = __riscv_vle64_v_u64m4(var_67, 3);
// 16090077958295291976, 5058025570064596806, 18331694445854200932

__riscv_vsetvl_e64m4(5);
vuint64m4_t var_28 = __riscv_vle64_v_u64m4(var_66, 5);
// 9277904776365247519, 6199737835434958138, 16283102520881457795, 11745254990704327140, 10064759157889306246

__riscv_vsetvl_e64m4(1);
vuint64m4_t var_29 = __riscv_vle64_v_u64m4(var_65, 1);
// 5614222760803579557

__riscv_vsetvl_e32m2(7);
vuint32m2_t var_30 = __riscv_vle32_v_u32m2(var_64, 7);
// 1227690475, 1502107102, 801010141, 2126338631, 3025649616, 3487614245, 14569746

vfloat32m2_t var_32 = __riscv_vle32_v_f32m2(var_63, 7);
// -2.0946218785136287e-35, 2.521696536530322e+35, -9.183435412395947e+24, -8.624621714752208e+26, 6.165116599290094e-35, -7.285795718059635e-16, -1.8674702225979434e-33

vfloat32m2_t var_33 = __riscv_vle32_v_f32m2(var_62, 7);
// -1.1827770064878237e+26, -1.3111533152679839e-36, 8.658888601896916e-18, -5.688580141840109e-26, 3.1488146125197364e+31, -677.9808349609375, 523593154822144.0

vint16m1_t var_34 = __riscv_vle16_v_i16m1(var_61, 7);
// -1663, 11444, -8810, 17993, -9281, 3460, -32008

vint8mf2_t var_35 = __riscv_vle8_v_i8mf2(var_60, 7);
// -31, -84, -128, 97, -3, -22, 77

vuint8mf2_t var_36 = __riscv_vle8_v_u8mf2(var_59, 7);
// 38, 115, 20, 210, 239, 182, 119

vuint64m4_t var_37 = __riscv_vle64_v_u64m4(var_58, 7);
// 16700153237887578248, 5031037798225230451, 5292105904994248007, 191847662260362543, 17224332114616326956, 10438953222179951407, 3274250116478307575

vuint64m4_t var_38 = __riscv_vle64_v_u64m4(var_57, 7);
// 5033313200475315879, 11361079409953223615, 7140048274794104683, 2981932693915571701, 9476848135713847987, 12261119440308053562, 9970426093577270632

__riscv_vsetvl_e64m4(3);
vuint64m4_t var_39 = __riscv_vle64_v_u64m4(var_56, 3);
// 2905331234579431349, 7092114374123614934, 10005960522681245691

__riscv_vsetvl_e64m4(2);
vuint64m4_t var_40 = __riscv_vle64_v_u64m4(var_55, 2);
// 6906626707180673736, 1475954422756504086

__riscv_vsetvl_e16mf2(4);
vint16mf2_t var_41 = __riscv_vle16_v_i16mf2(var_54, 4);
// 3175, 29167, -27933, 26903

__riscv_vsetvl_e64m4(7);
vuint64m4_t var_42 = __riscv_vle64_v_u64m4(var_53, 7);
// 11254251074008699435, 5204823814932142037, 8646232476803655494, 15091079855619697854, 12516473234604987981, 1630341543898427294, 1369196052764304654

vint64m4_t var_44 = __riscv_vle64_v_i64m4(var_52, 7);
// 2989185173643568993, -1007222647130467543, 9035883417988087253, 356697895597171625, -688843516243652996, 8367631197042162633, 7921162693062268499

__riscv_vsetvl_e64m4(5);
vuint64m4_t var_45 = __riscv_vle64_v_u64m4(var_51, 5);
// 6626590334479776340, 2241199338160557252, 16060726272050137143, 17732233298880458138, 7263785864330966034

__riscv_vsetvl_e64m4(7);
vuint64m4_t var_46 = __riscv_vle64_v_u64m4(var_50, 7);
// 4933956119501726389, 6288763602173540886, 5410560154821202561, 17226305573183414225, 7665224654860515905, 6322483520866588520, 792086670759048161

__riscv_vsetvl_e32m4(7);
vbool8_t var_22 = __riscv_vmslt_vx_i32m4_b8(var_23, var_48, 7);
// 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

__riscv_vsetvl_e64m4(8);
__riscv_vsse64_v_u64m4(var_74, var_75, var_24, 8);
__riscv_vsetvl_e64m4(4);
__riscv_vsse64_v_u64m4(var_76, var_77, var_25, 4);
__riscv_vsetvl_e64m4(6);
__riscv_vsse64_v_u64m4(var_78, var_79, var_26, 6);
__riscv_vsetvl_e64m4(3);
__riscv_vsse64_v_u64m4(var_80, var_81, var_27, 3);
__riscv_vsetvl_e64m4(5);
__riscv_vsse64_v_u64m4(var_82, var_83, var_28, 5);
__riscv_vsetvl_e64m4(1);
__riscv_vsse64_v_u64m4(var_84, var_85, var_29, 1);
__riscv_vsetvl_e32m2(7);
vbool16_t var_31 = __riscv_vmflt_vv_f32m2_b16(var_32, var_33, 7);
// 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

vbool16_t var_9 = __riscv_vmadc_vv_u64m4_b16(var_37, var_38, 7);
// 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

__riscv_vsetvl_e64m4(3);
__riscv_vsse64_v_u64m4(var_86, var_87, var_39, 3);
__riscv_vsetvl_e64m4(2);
__riscv_vsse64_v_u64m4(var_88, var_89, var_40, 2);
__riscv_vsetvl_e16mf2(4);
int16_t var_6 = __riscv_vmv_x_s_i16mf2_i16(var_41);
// 3175

__riscv_vsetvl_e64m4(7);
vbool16_t var_43 = __riscv_vmsgt_vx_i64m4_b16(var_44, var_47, 7);
// 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

__riscv_vsetvl_e64m4(5);
__riscv_vsse64_v_u64m4(var_90, var_91, var_45, 5);
__riscv_vsetvl_e64m8(7);
vuint64m8_t var_19 = __riscv_vsbc_vvm_u64m8(var_20, var_21, var_22, 7);
// 1022779765633755549, 17935306811229140577, 17221724369435699125, 15061971275327810052, 13005726497157586263, 4436412244169350869, 15728201342694651764

if(!check(var_74, var_127, var_128)) {cerr << "check 126 fails" << endl; return_value = 1;}
if(!check(var_76, var_124, var_125)) {cerr << "check 123 fails" << endl; return_value = 1;}
if(!check(var_78, var_121, var_122)) {cerr << "check 120 fails" << endl; return_value = 1;}
if(!check(var_80, var_118, var_119)) {cerr << "check 117 fails" << endl; return_value = 1;}
if(!check(var_82, var_115, var_116)) {cerr << "check 114 fails" << endl; return_value = 1;}
if(!check(var_84, var_112, var_113)) {cerr << "check 111 fails" << endl; return_value = 1;}
__riscv_vsetvl_e32m2(7);
vbool16_t var_12 = __riscv_vmsbc_vxm_u32m2_b16(var_30, var_49, var_31, 7);
// 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

if(!check(var_86, var_109, var_110)) {cerr << "check 108 fails" << endl; return_value = 1;}
if(!check(var_88, var_106, var_107)) {cerr << "check 105 fails" << endl; return_value = 1;}
if(!check(var_90, var_103, var_104)) {cerr << "check 102 fails" << endl; return_value = 1;}
__riscv_vsetvl_e64m8(7);
uint64_t var_11 = __riscv_vmv_x_s_u64m8_u64(var_19);
// 1022779765633755549

__riscv_vsetvl_e8mf2(7);
vint16m1_t var_10 = __riscv_vwmaccsu_vv_i16m1_mu(var_12, var_34, var_35, var_36, 7);
// -2841, 1784, -11370, -27173, -9998, -544, -22845

vuint64m4_t var_4 = __riscv_vsbc_vxm_u64m4(var_42, var_11, var_43, 7);
// 10231471308374943886, 4182044049298386488, 7623452711169899944, 14068300089985942305, 11493693468971232432, 607561778264671745, 346416287130549105

vbool16_t var_5 = __riscv_vmadc_vxm_i16m1_b16(var_10, var_6, var_9, 7);
// 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

vuint64m4_t var_2 = __riscv_vadd_vx_u64m4_mu(var_5, var_4, var_46, var_11, 7);
// 5956735885135481938, 4182044049298386488, 7623452711169899944, 14068300089985942305, 11493693468971232432, 7345263286500344069, 346416287130549105

__riscv_vsse64_v_u64m4(var_94, var_95, var_2, 7);
__riscv_vsetvl_e64m4(6);
__riscv_vsse64_v_u64m4(var_92, var_93, var_2, 6);
if(!check(var_94, var_97, var_98)) {cerr << "check 96 fails" << endl; return_value = 1;}
if(!check(var_92, var_100, var_101)) {cerr << "check 99 fails" << endl; return_value = 1;}
if (return_value)
  __builtin_abort ();
return return_value;
}
