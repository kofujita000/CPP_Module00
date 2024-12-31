#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string buff;       // 文字列バッファ

    switch (argc) {
        case (1):       // 引数入力がなかった場合
            buff.assign("* LOUD AND UNBEARABLE FEEDBACK NOISE *");
            break;

        default:        // 引数入力があった場合
            // 文字列を結合する
            for (int j = 1; j < argc; j ++)
                buff.append(argv[j]).push_back(' ');
            // 文字列の末尾の空白を削除する
            buff.erase(buff.end() - 1);
    }

    // 小文字を大文字に変換する
    for (std::string::iterator iter = buff.begin(); iter < buff.end(); iter ++) {
        ('a' <= *iter && *iter <= 'z' ? *iter -= 0x20 : 0);
    }
    // 出力する
    std::cout << buff << std::endl;

    return 0;
}
