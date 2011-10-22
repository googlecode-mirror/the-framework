<?php
/**
 * functions.inc
 *
 * File that conatains several helper functions.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 *
 */
/**
 * Função que recebe um assoc array e insere uma par key/value
 * no array.
 *
 * @param array  &$arr o array
 * @param string $key  a chave de inserção
 * @param mixed  $val  o valor
 *
 * @return int
 */
function array_unshift_assoc(&$arr, $key, $val)
{
    $arr = array_reverse($arr, true);
    $arr[$key] = $val;
    $arr = array_reverse($arr, true);
    return count($arr);
}
/**
 * Função que converte todos os elementos de um array para UTF-8.
 * Deve ser usado por exemplo quando se devolve algum array com
 * texto, por AJAX e no formato JSON, que suporta apenas esta
 * codificação.
 *
 * The arr element is passed by reference
 *
 * @param array &$arr the array to be encoded
 *
 * @return int
 */
function utf8_encode_assoc_array(&$arr)
{
    foreach ($arr as $key => $value) {
        $arr[$key] = utf8_encode($value);
    }
    return count($arr);
}
/**
 * Validates is an element received from the client side exists/ is empty.
 *
 * @param string $v the checked value
 *
 * @return boolean
 */
function filter_validate_not_empty($v)
{
    if ($v === null || $v === '') {
        return false;
    } else {
        return $v;
    }
}
/**
 * Validates if a value is null, empty or numeric.
 * 
 * @param mixed $v the checked value
 * 
 * @return boolean
 */
function filter_validate_numeric_or_empty($v)
{
    if ($v === null || $v === '') {
        return true;
    } else {
        return is_numeric($v);
    }
}
/**
 * Validates is an element received is a date.
 *
 * @param string $v the checked value.
 *
 * @return boolean
 */
function filter_validate_date($v)
{
    $s_regexp = '/^([\d]){4}([.-\s\/\\\])(0[1-9]|1[012])\2(0[1-9]|[12][0-9]|3[01])$/';
    return filter_var($v, FILTER_VALIDATE_REGEXP, array('options' => array('regexp' => $s_regexp)));
}
/**
 * Validates is an element received is a phone number.
 *
 * @param string $v the checked value.
 *
 * @return boolean
 */
function filter_validate_phone_number($v)
{
    $s_regexp = '/^[\d\s+]{1,}$/';
    return filter_var($v, FILTER_VALIDATE_REGEXP, array('options' => array('regexp' => $s_regexp)));
}

global $messages;
$messages = array();

/**
 * Writes an error message. If debug mode is enabled it will add a message to the
 * global messages variable.
 *
 * @param string $prefix a group identifier for the messages.
 *                       It can be a file name or class name.
 * @param string $msg    the error message
 *
 * @return void
 */
function write_error_msg($prefix, $msg)
{
    global $debug;
    global $messages;
    global $start_time;

    if ($debug === true) {
        $exec_time = round(microtime(true) - $start_time, 5);
        $messages[] = array("error", $prefix, $msg, $exec_time);
    }
}
/**
 * Writes an info message. If debug mode is enabled it will add a message to the
 * global messages variable.
 *
 * @param string $prefix a group identifier for the messages.
 *                       It can be a file name or class name.
 * @param string $msg    the error message
 *
 * @return void
 */
function write_info_msg($prefix, $msg)
{
    global $debug;
    global $start_time;
    global $messages;

    if ($debug === true) {
        $exec_time = round(microtime(true) - $start_time, 5);
        $messages[] = array("info", $prefix, $msg, $exec_time);
    }
}
/**
 * Writes a warning message. If debug mode is enabled it will add a message to the
 * global messages variable.
 *
 * @param string $prefix a group identifier for the messages.
 *                       It can be a file name or class name.
 * @param string $msg    the error message
 *
 * @return void
 */
function write_warn_msg($prefix, $msg)
{
    global $debug;
    global $start_time;
    global $messages;

    if ($debug === true) {
        $exec_time = round(microtime(true) - $start_time, 5);        
        $messages[] = array("warn", $prefix, $msg, $exec_time);
    }
}

/**
 * Limits debugging to a local environment
 */
function canDebug()
{
    $allowed = array ('127.0.0.1');
    return in_array($_SERVER['REMOTE_ADDR'], $allowed);
}
/**
 * Flushes the messages in the message array to a table.
 *
 * @return void
 */
function flush_msgs()
{
    global $messages;

    echo (
        "<doctype html>\n" .
        "    <html>\n" .
        "        <head>\n" .
        "            <title>Debug Output</title>" .
        "            <style>\n" .
        "              table {border-collapse:collapse;width: 100%;float:left;}".
        "              thead {background-color: grey;}\n" .
        "              thead th {border: 1px solid black;}\n" .
        "              tr {margin: 5px 0;}\n" .
        "              tr.info {background-color: green;color:white;}\n" .
        "              tr.error {background-color: red;color: white;} \n" .
        "              tr.php-error {background-color: black; color: white;}" .
        "              tr.warn {background-color: orange;}\n" .
        "              td {padding: 5px 5px;}\n" .
        "              td.neutral {background-color: yellow;color: black;}\n" .
        "              td {border: 1px solid black;}".
        "              .centered {text-align: center;}\n" .
        "              .right {text-align: right;}\n" .
        "            </style>\n" .
        "        </head>\n" .
        "        <body>\n" .
        "<table> \n" .
        "    <thead>\n" .
        "        <tr>\n" .
        "            <th>#</th>\n" .
        "            <th>Where</th>\n" .
        "            <th>Message</th>\n" .
        "            <th width='140px;'>Time</th>\n" .
        "        </tr>\n" .
        "    </thead>\n" .
        "    <tbody>\n");
    $i = 1;
    foreach ($messages as $message) {
        $message_text = $message[2];
        if (is_array($message_text)) {
            $message_text_tmp = "<p>Trace:</p>";
            foreach ($message_text as $line) {
                if (isset($line['file'])) {
                    $file = $line['file'];
                    $line_err = $line['line'];
                    $func = $line['function'];
                    $args = "";
                    for ($j = 0; $j < sizeof($line['args']); $j++) {
                        $arg = $line['args'][$j];
                        $args .= "{$arg}";
                        if ($j < sizeof($line['args']) -1 ) {
                            $args.= ",";
                        }
                    }
                    $message_text_tmp .=
                        "<p>@ {$file}:$line_err -> {$func}({$args})</p>";
                } else {
                    $message_text_tmp .= $line;
                }
            }
            $message_text = $message_text_tmp;
        }
        echo(
            "<tr class=\"{$message[0]}\"> \n" .
            "    <td class='centered neutral'>{$i}</td>\n" .
            "    <td class='centered neutral'>{$message[1]}</td>\n" .
            "    <td class=''>{$message_text}</td>\n" .
            "    <td class='right neutral'>@ {$message[3]} seconds</td>\n" .
            "</tr>\n"
            );
            $i++;
    }

    echo (
        "</tbody></table></body></html>"
        );
}
/**
 * The application error handler. If debug is enabled the error will be written into
 * the messages array.
 *
 * @param string $errno   the error number
 * @param string $errstr  the error message
 * @param string $errfile the file where the error ocurred
 * @param string $errline the line the trigered the error
 *
 * @return void
 */
function err_handler($errno, $errstr, $errfile, $errline)
{
    global $debug;
    global $messages;
    global $start_time;

    if ($debug === true) {
        $date = explode(" ", microtime());
        $microsecs = sprintf("%F", $date[0] - $start_time);
        $messages[] = array(
            "error",
            "PHP",
            "<p>{$errstr}</p><p>File: {$errfile}:$errline</p>",
        $microsecs
        );
    }
}

set_error_handler('err_handler');

/**
 * The application shutdown function. If the shutdown cause is an error it will be
 * added to the messages array. If debug mode is enabled the function flush_msgs is
 * called to render the messages table.
 *
 * @uses flush_msgs
 *
 * @return void
 */
function shutDownFunction()
{
    global $debug;
    $error = error_get_last();

    if (true === $debug && (!isset($_SERVER['HTTP_X_REQUESTED_WITH']))) {
        global $debug;
        global $messages;
        global $start_time;

        if ($error !== null) {
            $date = explode(" ", microtime());
            $microsecs = sprintf("%F", $date[0] - $start_time);
            $errstr = $error['message'];
            $errfile = $error['file'];
            $errline = $error['line'];
            $messages[] = array(
                "php-error",
                "PHP Shutdown",
                "<p>{$errstr}</p><p>File: {$errfile}:$errline</p>",
            $microsecs
            );
        }
        flush_msgs();
    }
}

register_shutdown_function('shutdownFunction');