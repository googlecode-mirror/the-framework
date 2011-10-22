<?php
/**
 * Registry.inc
 *
 * This file contains the Framework_Registry class.
 *
 * PHP versions 4 and 5
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  SVN: 1
 */
/**
 * This class is used to hold application wide variables.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_Registry
{
    private static $_vars = array();

    /**
     * Sets a value in the registry
     *
     * @param string $k the key for the value
     * @param mixed  $v the value
     *
     * @access public
     * @return void
     */
    public static function set($k, $v)
    {
        self::$_vars[$k] = $v;
    }

    /**
     * Returns a value in the registry
     *
     * @param string $k the key for the value
     *
     * @access public
     * @return mixed
     */
    public static function get($k)
    {
        if (isset(self::$_vars[$k])) {
            return self::$_vars[$k];
        }
    }
}