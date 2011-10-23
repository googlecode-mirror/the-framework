<?php
/**
 * autoload.inc
 * 
 * File that contains the autoload function for the framework.
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
 * __autoloadFramework
 * 
 * @param string $class_name the name of the class being loaded
 *
 * @return boolean
 */
function __autoloadFramework($class_name)
{
    $class_path = str_replace('_', '/', $class_name);
    $file_name = null;
    $paths = array(
        BASE_PATH . '/library/',
        BASE_PATH . '/application/'
    );
    foreach ($paths as $path) {
        $inc_ext = $path . $class_path . '.inc';

        write_info_msg("Including", $inc_ext);

        if (file_exists($inc_ext)) {
            include $inc_ext;  
            return true;
        }
    }

    write_warn_msg("File", "{$class_path} not found.");
    return false;
}
spl_autoload_register('__autoloadFramework');