<?php
/**
 * route.inc
 *
 * This file creates the Request object reading the REQUEST_URI.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html.
 */
$request_uri = $_SERVER['REQUEST_URI'];
write_info_msg("Route", $request_uri);

$clean_uri = explode("?", $request_uri);
$data_uri = explode("/", $clean_uri[0]);
array_shift($data_uri);

if (sizeof($data_uri) !== 2) {
    $size = sizeof($data_uri);
    write_warn_msg("Route", "Error parsing URI. Found size {$size} and expected 2.");
    $data_uri[0] = 'index';
    $data_uri[1] = 'index';
}

$request = new Framework_Request($data_uri[0], $data_uri[1]);
write_info_msg("Route", "Created Request for {$data_uri[0]}->{$data_uri[1]}");