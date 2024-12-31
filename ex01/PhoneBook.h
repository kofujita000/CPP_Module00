#pragma once

#include <cstring>

#define PHONE_BOOK_PERSONAL_INFO_SIZE 8

class PhoneBook {
    public:
        // 個人情報
        struct PersonalInfo {
            char    first_name[12];         // 名前
            char    family_name[12];        // 名字
            char    nick_name[12];          // 渾名
            char    phone_number[11];       // 電話番号
            char    darkest_secret[12];     // 秘密

            PersonalInfo(void);
            ~PersonalInfo(void);
        };

    private:
        // 個人情報のインスタンス
        PersonalInfo    personal_info[PHONE_BOOK_PERSONAL_INFO_SIZE];
        // 最新の情報を保持するインスタンスのインデックス
        std::size_t     personal_info_point;

    public:
        PhoneBook(void);

    public:
        /**
         * 情報を設定するための関数
         */
        void add(
                const PersonalInfo &personal_info);

        /**
         * 電話番号から登録されている情報を探してその情報のアドレスを返す関数
         *
         * 1. const char *const -> 電話番号
         * 2. const std::size_t -> 検索結果から何番目か
         *
         * r. const PersonalInfo* [!nullptr => 登録されている情報]
         *                        [nullptr  => 登録結果なし]
         */
        const PhoneBook::PersonalInfo *search(
                const char *const phone_number,
                const std::size_t count);
};
