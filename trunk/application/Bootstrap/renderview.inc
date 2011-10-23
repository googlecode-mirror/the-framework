<?php
/**
 * renderview.inc
 *
 * This is file is the final step in the bootstraping process and is
 * responsible for the interaction with Smarty, which finally renders
 * the View template.
 *
 * PHP Version 4 and 5
 *
 * @category Application
 * @package  Bootstrap
 * @author   Tiago Seixas <tiagoafseixas@gmail.com>
 * @license  GPLv3 http://www.gnu.org/licenses/gpl.html.
 */
if (false === $request instanceof Framework_Request) {
    write_error_msg("Render View", "Request object not instantiated.");
} else {
    $response = $controller->getResponse();

    switch ($response->getResponseType()) {
    case Framework_Response::RESPONSE_TYPE_JSON:
        header('Content-type: application/json');
        echo json_encode($response->getJSONResponse());
        break;
    default:
        $smarty = $controller->getView();

        if ($response->hasError()) {
            $smarty->assign('error_msg', $response->getErrorMessage());
            $action_nm = 'application';
            $request->setController('error');
        }
        $view_path = '/application/View/';
        $smarty->template_dir = BASE_PATH .
            "{$view_path}templates/{$request->getController()}";
        $smarty->compile_dir = BASE_PATH . 
            "{$view_path}templates_c/{$request->getController()}";
        $smarty->cache_dir = BASE_PATH . 
            "{$view_path}cache/{$request->getController()}";
        $template_path = "{$smarty->template_dir}/{$action_nm}.tpl";
        if (false === file_exists($template_path)) {
            write_error_msg(
                "Render View",
                "Template file {$template_path} not found."
            );
        } else {
            write_info_msg("Render View", "Loading template {$template_path}");
            $smarty->assign(
                'http_static_context',
                Framework_Registry::get('HTTP_STATIC_CONTEXT')
            );
            $smarty->assign('xml_http_request', $request->isXmlHttpRequest());
            $smarty->registerPlugin('block', 't', 'smarty_block_t');

            if (false === $request->isXmlHttpRequest()) {
                $navigation = new Framework_Navigation();
                $navigation->setCurrentController($request->getController());
                $navigation->setCurrentAction($action_nm);
                $smarty->assign('navigation', $navigation, true);
                $mem = round((memory_get_usage(true) / 1024), 2);
                $smarty->assign('memory', $mem);
                $exec_time = round(microtime(true) - $start_time, 5);
                $smarty->assign('exec_time', $exec_time);
                if (true === isset($_SESSION['session_user_nm'])) {
                    $arr_name = explode(' ', $_SESSION['session_user_nm']);
                    $smarty->assign('full_name', $arr_name[0]);
                }
                try {
                    $smarty->display("{$action_nm}.tpl");
                } catch (Exception $e) {
                    write_error_msg("Render View", $e->getTrace());
                    //@todo render view app1l error
                }
            } else {
                echo $smarty->fetch($action_nm . '.tpl');
            }
        }
        break;
    }
}
write_info_msg("Render View", "done");