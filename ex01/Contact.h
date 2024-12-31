#pragma once

#include <iostream>
#include <unistd.h>

#include "PhoneBook.h"

#define CONTACT_INPUT_COMMAND_SIZE  7
#define CONTACT_BUFF_SIZE           16
#define CONTACT_INPUT_ERROR_MSG "Incorrect command."
#define CONTACT_INPUT_RANGE_MSG "Incorrect string length.(10)"

#define CONTACT_CMD_ADD     "ADD"
#define CONTACT_CMD_SEARCH  "SEARCH"
#define CONTACT_CMD_EXIT    "EXIT"

class Contact {
    private:
        // コマンドをプログラム上で扱うためのもの
        enum Command {
            COMMAND_ADD = 0,        // ADD    command
            COMMAND_SEARCH,         // SEARCH command
            COMMAND_EXIT,           // EXIT   command
            COMMAND_UNKNOWN,        // 特定不能
        };

    private:
        PhoneBook   phone_book;     // 個人情報を保持するもの

    public:
        /**
         * ユーザと対話的に処理を行うための関数
         */
        void run(void);

    private:
        /**
         * コマンドをユーザに入力させる関数
         *
         * 1. char [CONTACT_INPUT_COMMAND_SIZE] -> 入力値を設定するもの
         */
        void inputCommand(
                char cmd_str[CONTACT_INPUT_COMMAND_SIZE]);

        /**
         * コマンドを識別するための関数
         *
         * 1. const char *const -> コマンド文字列
         * 2. Contact::Command& -> コマンド変換後の代入先
         *
         * r. bool -> [true => 処理成功] / [false => 変換失敗]
         */
        bool convertStringToCommand(
                const char *const str,
                Contact::Command &cmd);

    private:
        /**
         * 情報を代入する処理を行う関数
         *
         * r. bool -> [true  => 処理成功]
         *            [false => 入力されたパラメータの長さが対応範囲外]
         */
        bool addPhoneBook(void);

        /**
         * 情報を検索する処理を行う関数
         *
         * r. bool -> [true => 処理成功]
         *         -> [false => 入力されたパラメータの長さが対応範囲外]
         */
        bool searchPhoneBook(void);

        /**
         * パラメータ情報を取得するための関数
         *
         * 1. char [CONTACT_BUFF_SIZE] -> 文字列を代入する場所
         * 2. const std::size_t        -> 文字列の最大長 (CONTACT_BUFF_SIZE以下)
         * 
         * r. bool -> [true => 処理成功]
         *         -> [false => 入力されたパラメータの長さが対応範囲外]
         */
        bool inputParameter(
                char buff[CONTACT_BUFF_SIZE],
                const ::ssize_t max);

        /**
         * 出力情報を作成する関数 (右空白うめを行う)
         *  
         *  > 最大文字数以上になった場合その番号に '.' を入れる
         *
         * 1. char [CONTACT_BUFF_SIZE] -> 文字列を代入する場所
         * 2. const char *             -> 代入対象文字列
         * 3. std::size_t              -> 文字列の長さ
         */
        void makeOutputValue(
                char response[CONTACT_BUFF_SIZE],
                const char *request,
                const ::ssize_t max);

    private:
        /**
         * read を解放するための関数
         */
        void clearRead(void);
};
