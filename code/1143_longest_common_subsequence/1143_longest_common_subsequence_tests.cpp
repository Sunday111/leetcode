#include "1143_longest_common_subsequence.hpp"
#include "gtest/gtest.h"

TEST(t1143_longest_common_subsequence, test_1)
{
    ASSERT_EQ(Solution{}.longestCommonSubsequence("abcde", "ace"), 3);
    ASSERT_EQ(Solution{}.longestCommonSubsequence("abc", "abc"), 3);
    ASSERT_EQ(Solution{}.longestCommonSubsequence("abc", "def"), 0);
}

TEST(t1143_longest_common_subsequence, test_2)
{
    ASSERT_EQ(Solution{}.longestCommonSubsequence("a", "ttta"), 1);
}

TEST(t1143_longest_common_subsequence, test_3)
{
    ASSERT_EQ(Solution{}.longestCommonSubsequence("wggi", "g"), 1);
}

TEST(t1143_longest_common_subsequence, test_4)
{
    ASSERT_EQ(Solution{}.longestCommonSubsequence("iitt", "tttttttttt"), 2);
}

TEST(t1143_longest_common_subsequence, test_5)
{
    ASSERT_EQ(Solution{}.longestCommonSubsequence("jijiijjpji", "jjji"), 4);
}

TEST(t1143_longest_common_subsequence, test_6)
{
    ASSERT_EQ(
        Solution{}.longestCommonSubsequence(
            "fnbeaucuyhgariizanpxffiiicvjcynwcvlqyvobxvmqpqelcqrdvggecbwrhrwyqb"
            "gafyrnmwqrbtugykagycteuusvkpthokeiqddumbgwzechfyxrqxwfzmcpkewebbha"
            "owqjalzqpkwzfyymttnatmczxbnmydnzfongvdokxjwibilpitdxfwavtkftdenrzs"
            "ktqlsptsccttizehxvellkmqnomfynnptzcwseragirexubilbnxddsmmwufhcijrs"
            "dmecixjbahrhhkrekuqqcdghnljlazvvvtziqaimkfqignlmmfzujeboaqqeswjseo"
            "zaspgpbedwwheshjettreroubajeaqfbrzlpehcnurcdeimkofesjgcmtqrdjwvsua"
            "gtszyxaqmctdusuyjdlwedsjrdpnsdizoflilgvkjdbdxhqtnguqjzkjknpbvawoyw"
            "klsfvnlkhlfmvbanxtypouejervclgkinohleenbsrvddvhjeelokbtuikrfilyyer"
            "qamcanglbdihfffociwoloifuipddpnccwzlpqblpohjstiygligyibclnewnhgdjj"
            "atspmtphgddgyfdpizyengteffdwrkswjwuznebeougvojdzzztaallammgskuzrjh"
            "wxonzogekpderhzdehbzgcxgveaxiyrptakpblbsmmuwwmtmiezgghvesvqtgdiazz"
            "kboitidoeeookdfvgcujpvixvzzzakbwkynicutzowvzfspxfkndfvodvpwadlrvsw"
            "almpdhllilhmofyoyaxhncjmhqghadfajienejnihwniubbajajyzpxvuraorjnkgo"
            "njvnmdboujfyoimsqdfebutbjcqgvdkkgczzwruinxsltspempsvclpzgqwybsquxu"
            "bmvzygkpabvkchieqtvqdocjpufcmojehiwdnmvzgrsfgiwqmiahmozjzqzzfzrtxn"
            "qistceggdm",
            "vfkfjkpuyo"),
        10);
}

TEST(t1143_longest_common_subsequence, test_7)
{
    ASSERT_EQ(
        Solution{}.longestCommonSubsequence(
            "fffkvfffkkkkkffffffkvfvvvfffvvvkffkfkfkvvvkkvfkvvvkvvffvvkvfvvfkff"
            "vfffkkffkfvkkkffffvfkvfvvvffvvkkvvkvvvfvfvvkfkfvfvvfvvffkvkfkkkkvv"
            "ffkkfvvvkvkvvfvvvkkfkvffkfkffkfffvkvkfvkvfkvffkkvkfkffkfvkffvvkkfk"
            "kvvvkfffkfkvfkffvfvkfvkkvkvffvvfkvvffkvkkfkffkvfkffkkffkkkfkvfvfkf"
            "vvfkvfvkfvkkfkvvkkfkfvvfvkkffffkkkvffkfvvkkfkkvvvffffvvvvkffkffkvk"
            "vkvvkvfffvfkkfffkvvvkfvvfvvvfkfkfkfvfffkvkvfkvfkffkvkkvvkkfkkvkfkv"
            "vfvffkkkkkfffvkfvkfkkkkvkkvvkkfvvvfkvvfkvffvvfkkfkfkfvvkfkkvvkkfvv"
            "kvvkfffkvvvkffvfkkfkfvvkkkkfkvvfvkfkfkvvfvkkvfvfkfvvkvfkkkkvvffvfv"
            "ffvvvvvfkkkfkvvfkvvffkkkvkfkkfkfkkkffffvvkvvvfkvkfkffffvfvvvfvkvvk"
            "kkkvkkkkvvfvfkvvkkkfkkvfkkfffvfkvkvffvkfvvkkfkfvvkfvkffkfvvkkvfkvf"
            "ffffvkkfkfkkkkkfkvvvfkvvvffffkfffvfvkvvfvkkfkkvfkkkkfkfkvvkffkkvkk"
            "fvffvkvfvfffffvvfvvvvvvkfvvfvfkfvvvvkffffvkkfkkfvvkfffkkvvkkvfkvkk"
            "fvkkvffkfkvkffvfkkkfkkvvvvkkvvfvfkkkfvkvfkkkfkkfkvkvvvkvfffkvkfkvf"
            "kkvvvkkffkvfvfkkvkffffvfkkfvfkfvffvvvkkfvfvvvfkkkkkkvfvkvkkkfvfkkf"
            "fvkvkkvfvkkkvfkkfvfffkvvvfkfffvvvfkffvvfkfvkfkfffkkkvffvvvkfkkkvvk"
            "kkkkfvvkvf",
            "vkkkkkffvk"),
        10);
}

TEST(t1143_longest_common_subsequence, test_8)
{
    ASSERT_EQ(
        Solution{}.longestCommonSubsequence(
            "jduirerawykaiwuavukhrzhrkmrrsgvhkvorntvritqrikfrsowwvqqqmhlhotjhej"
            "vsqgcdooqxddogyuknrlircvibjrvpnagltihrkporzbpcopxshjpnotcrdtwomegq"
            "vlbbwhnaxgiiyojgzcdjzapcxsdjryotvpybpyrpomtbxtjmeionxqmypkhtwklicx"
            "oahrggebhisypyjepbehretsucyjbycemhochgexmjryiehrkvjpaflpkdeqzvmlxz"
            "fddgqfzpugqxufqgsdomwtwlulyzoghcadlkizvxxkjuucycgkaaiyxbtchgkrlmgo"
            "yiybooskaimdmbgdunnaetobnvdmafxflddipayovckxclvrhvcvwkxkzcchecswec"
            "dpjhbmgyqpvhbuvjefuqjryfiemmolboenvqebszzphxxircsreeyyybvkndakdtgb"
            "zfhprcxzzpvhwsqfjxxphgxirciruvlpzirfkengtlihkftqwbxxbizgdosnkorwdc"
            "tuadclrdxpbtasewryelndvpbqeovpjxfkpsieauewhvourullpeeergppcajiglrp"
            "ubywcngksnltjucbaapjpphcrbhdnldhobvtpgmzulzcfcrrwmqorxobnugdrspdxl"
            "crahlsiadousabbneeasaxpwvkwkajiliqqjjbuautnmorrmhkpbagztvhotxlwrxx"
            "wfpwbamhjogguaubvyhtthjcgybyszjsazqtodwsshxargcydrbpdqgeehzpzjeckq"
            "jvuhdnkjffhmgbywhkcvzinqvhjqqtgvzildpjlnummlxmbqsrxtpwcpgezhxmphwo"
            "xzeruogaxytsyvrafqnowsskzhpfjruykkxftbxedznpmhcabdvwutnoyvwvzdheza"
            "gvlbbzihzpvrvvwnftgleyzyjldnfdwezzjsiinzqobgwevgifliyngizlkjyoawjl"
            "cmnkalyqfc",
            "bcrvkxirhlayhntityxpewodsaxukgleifcyfxzroxhekjqwhiltrahuwjjtqprhsa"
            "ajtojzaabgykkylnebewxjkwcchejchefbikcltdrrvfqfjdzeyqkinufmebjankix"
            "hdsvtynzheihvhceyuuwrqhoagyeihaimxuodjnkryflzqirsgoiithsrdecijeuyl"
            "fudpotgvhcmixjvlwnwdmpaukzmiatzvvbilydajfvhofewpxdzynchdcimywmunjh"
            "lndfaqecawmneinwazlvuafwghxqtbmunjbppgdpoklsqetuktjglkqelxknepxmpu"
            "pteauyimcrwqzdofthulkoqhmjsnstdsvbsvtunoiytycfvzaazxflusdbbylrhbvb"
            "dzayjjhuzptbfgpzhhozotgbmnhstopclzamvxstoukmqaeqryxjylubkojpyhrofc"
            "ngydxcurvncwbypfbqmhtflrfwdtckfowkjyareehfvkzjyhblenbimgjdtkgewmrz"
            "euiojkuaqwfibfsbbbqinxxfuezzhgrndzcrjqdfxjwnqsrhukncrmapdvgyjeibmm"
            "ewtwysuxddrtegebwpudmukgphrlwwopsyipooljpteojxyrkigtmhhntlhggdvguj"
            "pctycbebsszpwxzzxxmlwosoeerstgjwxdhctolxrfyeatdociyymxvqajikjxqxhf"
            "aegmudedtuiqmoouifvtxwhiyvkvpaljxhnfdgeraezjjthvktdibqtteaveqeikyl"
            "kdoudjxwlgmuyapghfjodmsttvlgnjgfvtcrjunqckgicztpxhpsoracexdafcwkqp"
            "eyjwxmhyjctbmngzqjfvnveruvlbpbldhgofofdkmvwgsnnzutlpjbmsoszsycvuhg"
            "oobxwiqnvwmqgcvcvyexvoxciqgwrvpdjmogqbmmoeymcbxbynljfwpjbklxszouox"
            "uuqrgmjwmq"),
        321);
}

TEST(t1143_longest_common_subsequence, test_9)
{
    ASSERT_EQ(
        Solution{}.longestCommonSubsequence(
            "qqqzqzqzqzqqqqzqqqqqqzqqqqqqzqqzqqqqqzzqzzqqqqzqqzqqqqzzqqzzzqqqzz"
            "qzzzzqzqqqqzzqzqqqqqqqqzzqzzzzqzqzqqqqqzqzqzzqqqzqqzzqqqzqqzqqzqzq"
            "zqqqqqzqzzzzqqqqqqzzzqqzqzqqzqqqqzqqzqzzzqqzqzzzzqqqqzzqqqqqqqqqqz"
            "qqqzqzqzqqzqqqzqqqzzqzqqqqqzqzqqqqzqqqqqqqzzqzqzqqqzqqzzqzqqqzqqqz"
            "zqqqqqzqzqzqqqqqqqqqqzqqzqzqqqqqqqzqzzqqqqqqzqqzqqqqzqqqzqqqqqzqqq"
            "qqzqqqzqzqzqqqzzqqqqzqqzzqqqzzqqqqzzzqqqqqqzqqzqqzqqqzzqqqqzzqqzzq"
            "zqzzqqqzqqqqzzqzqzzzzqqqzqzqzzqqzzqqqqqqzqqqqqqqqqzzqzqqqzqzqqqqqq"
            "qqqzqzqqzqqqzzqqzzqqqqqqqqqqqqzzqqqzqzqzqqqqqzqqqqzzqqzqqqzqzqzqqq"
            "zzqqqqqqqqqzqzqzqqqzzzqqqzzqqqzqzzqzzzqqzqqqqzqzqqzqzqqqqqqqqzzqqq"
            "zqzzqqqqzzqzzqzqqqqqqqzqqqzqqqqqqqqzqqqqzqqqzqzqqzqqzzzzqqzzqqzqqz"
            "qqqzqqqqqqqqqqqzzqzzqqqzqqqzqzzqqzqqqzzzqzqqqqqqqqqqqzzqqzqqqqzzqq"
            "qzqqzqqqqqqzqqqqqzqqqqqzzqqqzqqqqzzzqqqqqqzzzzqqqzqzqzqqqqzqqzzzzq"
            "qqqzqqqzzzqqzqzqzqzzqzzzqqzqqqzqqqzqzqqqzqqqqqzqqqzzqqqqzqqqzqzzqz"
            "zqqzqzzqqqqzqqqqqzqqqqqqqqqqzqqzzqqzzqqqqqzqqzzzzqqqqqqqqzqzzqqzzq"
            "zqqqqqqqzqqzqqqqqzqqqzqqzqzqzzqqzqzqqqzqzzqqzqqqqqqzqqqzzzqzqqqqqq"
            "qzqqqzzzqq",
            "qzqqqqqzzqqqqzqqzqzqqqqqqqzqqqzqqzzqqqqzzzzqqqqzqqqqzzqqzqqqqqzqzq"
            "zqzqzqqqzqzqqqqqqzzqqqqqqzqzzqqqqzqqqzqzzqqzqzqqzqzqqqqzqqzzzzqqzz"
            "qzqqzqzqqqqqzqzqzzqqzqzqqqqzqzzqqqqzzqzqqqzqqzqqqzqzqzqqqzzqqqqzqq"
            "qzqqqzqqzqqzqqzqqqqzqqqzzqzzqzzzqqqqqzqzqqqqqqzqqqqzqqqqqzzqqqqqzq"
            "zzqqqzqqqqqqqzzzzqqzzqqqzzqzqzqqqqqqzzzqzqqqzzzzzqzqqqqzqqqzqqqqqq"
            "qqzzqqqqzqqqqqqqzqqzzzqqqqzqqqqzzqzzqqzqqzqqzqzqzqzqqqqqqqqzzzqqqq"
            "zqzqqqzzqqqqzzqqqzqqqqqqzzzqqzqzqzqqqzqqqzqqqqqzqqzzqzqqqqqzqqqqqq"
            "qzqqqzqqqqqzqzqqqqqqzqqqqqzqqqzqqqzzqzzqqqqqqqzqqzqqzzzqqqzqqqqqqq"
            "qqzzzqzqqqqqqzqzqzqqqqqzqqqqqqqqzzqqqzqzqzzqqqqqqzqqqzqqqzqzqqqqzq"
            "qzqqqzqzzqqzzqzqqzqqqqzqqzqqqqzqqzzqqqqqqqzzqqqqzqzzzqzzzzqzqqqqqq"
            "zqzqqzqzqqzzzqzqqzqqzqqzzqzqqqzqqqqzqqqqqqqzqzqzqzqzzqqzqqqqzqqzqq"
            "qqqzqzqqqqzqzzqqzqzzqzqqqqzzqqqqqzqqzqqqqqqqqqqqqzqqzqqqzqqqqqqqqz"
            "qqzzqqqqqzzqqzqqqqzqzqzqzqqqqqqqqzzqqqzqqqzzqqqzzqzqqqzqqqzqqqqqqq"
            "zqqzqzqqqzzqzqqqqzqzqqzzzzqqqqzqzqqzqqqqzqzzqqzzzqzqzzzzqqzqzqqqqq"
            "zzqqqzzqqzqzzqqzzqqqqqqqzzzzqqqqqqqqqqqzqqqqqzzqqzzqzqqzzqqqzzqqqz"
            "qqzzqqqqzq"),
        831);
}
