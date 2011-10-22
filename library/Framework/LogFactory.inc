<?php
/**
 * LogFactory.inc
 *
 * This file contains the Framework_LogFactory class.
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
 * This returns a Log.
 *
 * @category Framework
 * @package  Framework
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html
 * @version  Release: 1
 */
class Framework_LogFactory
{
    /**
     * Returns a new Log
     * 
     * @param string $ident the identity that will show up in the log
     * 
     * @return Log
     */
    public static function getLog($ident)
    {
        return Log::factory(
            Framework_Registry::get('LOG_HANDLER'),
            Framework_Registry::get('LOG_PATH'),
            $ident
        );
    }
}