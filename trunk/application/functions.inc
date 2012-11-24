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
// ==================================================================================
// FILTER FUNCTIONS
// ==================================================================================
/**
 * Validates is an element received from the client side exists/ is empty.
 *
 * @param string $v the checked value
 *
 * @return boolean
 */
function filter_validate_not_empty($v)
{
    if (true === empty($v)) {
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
    $s_regexp
        = '/^([\d]){4}([.-\s\/\\\])(0[1-9]|1[012])\2(0[1-9]|[12][0-9]|3[01])$/';
    return filter_var(
        $v, FILTER_VALIDATE_REGEXP,
        array('options' => array('regexp' => $s_regexp))
    );
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
    return filter_var(
        $v, FILTER_VALIDATE_REGEXP,
        array('options' => array('regexp' => $s_regexp))
    );
}

global $messages;
$messages = array();
// ==================================================================================
// MESSAGE FUNCTIONS
// ==================================================================================
// These functions write messages (info, warning or error) either to an array of
// messages or to a log file when debug mode is not enabled.
/**
 * Writes an error message. If debug mode is enabled it will add a message to
 * the global messages variable.
 *
 * @param string $prefix a group identifier for the messages.
 *                       It can be a file name or class name.
 * @param string $msg    the error message
 *
 * @uses write_log_message
 *
 * @return void
 */
function write_error_msg($prefix, $msg)
{
    if (true === defined('DEBUG_ENABLED') && DEBUG_ENABLED === true) {
        $exec_time = round(microtime(true) - START_TIME, 5);
        global $messages;
        $messages[] = array("error", $prefix, $msg, $exec_time);
    } else {
        write_log_message($prefix, $msg, LOG_ERR);
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
 * @uses write_log_message
 *
 * @return void
 */
function write_info_msg($prefix, $msg)
{
    if (true === defined('DEBUG_ENABLED') && DEBUG_ENABLED === true) {        
        $exec_time = round(microtime(true) - START_TIME, 5);
        global $messages;
        $messages[] = array("info", $prefix, $msg, $exec_time);
    } else {
        write_log_message($prefix, $msg, LOG_INFO);
    }
}
/**
 * Writes a warning message. If debug mode is enabled it will add a message to
 * the global messages variable.
 *
 * @param string $prefix a group identifier for the messages.
 *                       It can be a file name or class name.
 * @param string $msg    the error message
 *
 * @uses write_log_message
 *
 * @return void
 */
function write_warn_msg($prefix, $msg)
{
    if (true === defined('DEBUG_ENABLED') && DEBUG_ENABLED === true) {
        $exec_time = round(microtime(true) - START_TIME, 5);
        global $messages;
        $messages[] = array("warn", $prefix, $msg, $exec_time);
    } else {
        write_log_message($prefix, $msg, LOG_WARNING);
    }
}

function write_debug_msg($prefix, $msg)
{
    if (true === defined('DEBUG_ENABLED') && DEBUG_ENABLED === true) {
        $exec_time = round(microtime(true) - START_TIME, 5);        
        global $messages;
        $messages[] = array("debug", $prefix, $msg, $exec_time);
    } else {
        write_log_message($prefix, $msg, LOG_DEBUG);
    }
}
/**
 * Limits debugging to a local environment
 *
 * @return boolean
 */
function can_debug()
{
    $allowed = array ('localhost', '127.0.0.1','::1');
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
        "              tr.debug {background-color: green;color:white;font-style:italic;}\n" .
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
 * The application error handler. If debug is enabled the error will be written
 * into the messages array.
 *
 * @param string $errno   the error number
 * @param string $errstr  the error message
 * @param string $errfile the file where the error ocurred
 * @param string $errline the line the trigered the error
 *
 * @uses write_log_message
 *
 * @return void
 */
function err_handler($errno, $errstr, $errfile, $errline)
{
    global $messages;

    if (true === defined('DEBUG_ENABLED') && true === DEBUG_ENABLED) {
        $date = explode(" ", microtime());
        $microsecs = sprintf("%F", $date[0] - START_TIME);
        $messages[] = array(
            "error",
            "PHP",
            "<p>{$errstr}</p><p>File: {$errfile}:$errline</p>",
        $microsecs
        );
    } else {
        write_log_message("ERROR HANDLER", "{$errstr} {$errfile}:$errline", LOG_ERR);
    }
}

set_error_handler('err_handler');

/**
 * The application shutdown function. If the shutdown cause is an error it will
 * be added to the messages array. If debug mode is enabled the function
 * flush_msgs is called to render the messages table.
 *
 * @uses flush_msgs
 *
 * @return void
 */
function shutDownFunction()
{
    $error = error_get_last();

    if (true === defined('DEBUG_ENABLED')
        && true === DEBUG_ENABLED
        && (!isset($_SERVER['HTTP_X_REQUESTED_WITH']))
    ) {
        global $messages;

        if ($error !== null) {
            $date = explode(" ", microtime(true));
            $microsecs = sprintf("%F", $date[0] - START_TIME);
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

/**
 * This function writes to the log defined in the ini file.
 *
 * @param string $msg_ident The identity of the element writing this msg
 * @param mixed  $msg       The message being written to the log
 * @param int    $level     The log level for this message
 *
 * @uses Framework_Registry
 * @uses log_roller
 *
 * @return void
 */
function write_log_message($msg_ident, $msg, $level = LOG_INFO)
{
    if(false == is_writable(Framework_Registry::get('LOG_PATH'))) {
        return false;
    }

    if ($level <= DEFAULT_LOG_LEVEL) {
        $date = date('D M d H:i:s Y');
        switch ($level) {
        case LOG_INFO:
            $level_desc = 'INFO';
            break;
        case LOG_DEBUG:
            $level_desc = 'DEBUG';
            break;
        case LOG_WARNING:
            $level_desc = 'WARNING';
            break;
        case LOG_ERR:
            $level_desc = 'ERROR';
            break;
        case LOG_ALERT:
            $level_desc = 'ALERT';
            break;
        default:
            $level_desc = 'INFO';
            break;
        }

        // create the message prefix: date, remote address and the identity
        $log_msg = sprintf(
            '[%s] [%s] [CLIENT %s] [%s] ',
            strtoupper($date),
            $level_desc,
            $_SERVER['REMOTE_ADDR'],
            strtoupper($msg_ident)
        );

        //before we write to the log we check if it's time to roll the log
        log_roller();

        if (is_a($msg, 'Exception')) {
            error_log(
                $log_msg . $msg->getMessage() . "\n",
                3,
                Framework_Registry::get('LOG_PATH')
            );
            $st = $msg->getTrace();
            $st_length = sizeof($st);
            for ($i = 0; $i < $st_length; $i++) {
                $err_msg = $st[$i];
                error_log(
                    $log_msg . sprintf(
                        "#%d %s() %s:%d",
                        $i,
                        $err_msg['function'],
                        $err_msg['file'],
                        $err_msg['line']
                    ) . "\n",
                    3,
                    Framework_Registry::get('LOG_PATH')
                );
            }
        } else {
            $log_msg .= $msg . "\n";
            error_log($log_msg, 3, Framework_Registry::get('LOG_PATH'));
        }
    }
}
/**
 * Function responsible for renaming the log file when it reaches the max size
 *
 * @uses Framework_Registry
 *
 * @return void
 */
function log_roller()
{
    $file = Framework_Registry::get('LOG_PATH');
    if (file_exists($file) && filesize($file) > (500 * 1024)) { // 500MB Max size
        rename($file, $file . time());
        clearstatcache();
    }
}
// ==================================================================================
// BREADCRUMB FUNCTIONS
// ==================================================================================
/**
 * Adds a breadcrumb item to the array
 *
 * @param string $text       the text displayed in the breadcrumb
 * @param string $controller the controller that invokes this action
 * @param string $action     the name of the action
 * @param string $url        the url placed in the href
 *
 * @return void
 */
function put_breadcrumb(
    $text, $controller,$action, $url = null
) {
    if (false === isset($_SESSION['breadcrumbs'])) {
        $_SESSION['breadcrumbs'] = array();
    }

    $breadcrumbs = $_SESSION['breadcrumbs'];
    $breadcrumbs_size = sizeof($breadcrumbs);

    for ($i = 0; $i < $breadcrumbs_size; $i++) {
        if ($breadcrumbs[$i]['controller'] === $controller
            && $breadcrumbs[$i]['action'] === $action
        ) {
            $breadcrumbs = array_slice($breadcrumbs, 0, $i, true);
            $_SESSION['breadcrumbs'] = $breadcrumbs;
            break;
        }
    }

    if ($url === null) {
        $url = $_SERVER['REQUEST_URI'];
    }

    $breadcrumb = array(
        'text'       => $text,
        'url'        => htmlentities($url),
        'action'     => $action,
        'controller' => $controller
    );

    $_SESSION['breadcrumbs'][] = $breadcrumb;
}
/**
 * Clears the breadcrumb array
 *
 * @return void
 */
function clear_breadcrumbs()
{
    $_SESSION['breadcrumbs'] = array();
}
/**
 * Returns the breadcrumb array
 *
 * @return array
 */
function get_breadcrumbs()
{
    if (true === isset($_SESSION['breadcrumbs'])) {
        return $_SESSION['breadcrumbs'];
    }
}
/**
 * A simple shell for the crypt function native in PHP to encrypt string using the
 * bcrypt algorithm. It generates a 16 byte salt using the md5 function to use as
 * a parameter.
 *
 * @param string $input  the string that is going to be encrypted
 * @param string $salt   the salt string
 * @param int    $rounds the cost parameter
 *
 * @see http://www.goodphptutorials.com/out/How_To_Safely_Store_A_Password
 *
 * @return string
 */
function bcrypt($input, $salt = 'salt', $rounds = 13)
{
    return crypt($input, '$2a$' . $rounds . '$' . md5($salt) . '$');
}
// ==================================================================================
// FORMAT FUNCTIONS
// ==================================================================================
function format_date_time($time)
{
    return true === empty($time) ? null : date('Y-m-d H:i:s', $time);
}

function format_date($date)
{
    return true === empty($date) ? null : date('Y-m-d', $date);
}

function format_time($time)
{
    return true === empty($time) ? null : date('H:i:s', $time);
}
