<?php
/**
 * @file
 * Theme functions for Socialfield, placed here for improved developer experience.
 */

/**
 * Custom theme output for widget.
 */
function theme_socialfield_drag_components($variables) {
  $element = $variables['element'];
  $unique = socialfield_random_string();
  backdrop_add_tabledrag('socialfield-table-' . $unique, 'order', 'sibling', 'item-row-weight');
  $config = config('socialfield.settings');
  $services = $config->get('services');

  $header = array(t($element['#title']), '', '', '', '');
  $rows = array();
  $index = 0;

  for ($i=0; $i<$element['#num_elements']; $i++) {
    while (!isset($element['element_' . $index])) {
      // There is no element with this index. Moving on to the next possible element.
      $index++;
    }
    $current_element = $element['element_' . $index];


    $machine_name = $current_element['#service'];
    // Sanitize
    $service_label = check_plain($services[$current_element['#service']]['label']);
    $icon_name = check_plain($services[$current_element['#service']]['iconapi']);
    if ($config->get('filled')) {
      $icon_name = check_plain($services[$current_element['#service']]['iconapi_fill']);
    }
    $icon_options = array(
      'attributes' => array(
        'class' => array('socialfield-' . $machine_name),
        'width' => 30,
        'height' => 30,
      ),
    );

    $rows[] = array(
      'data' => array(
        t($service_label),
        icon($icon_name, $icon_options),
        backdrop_render($current_element['url']),
        backdrop_render($current_element['weight']),
        backdrop_render($current_element['operation']),
      ),
      'class' => array('draggable'),
      'weight' => $current_element['weight']['#value'],
    );

    $index++;
  }

  // Sorting elements by their weight.
  backdrop_sort($rows, array('weight'));

  $description  = '<div class="description">';
  $description .= backdrop_render($element['description']);
  $description .= '</div>';

  $add_more = backdrop_render($element['add_one_social']) . $description;

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'id' => 'socialfield-table-' . $unique,
      'class' => array('socialfield-table'),
    ),
  )) . $add_more;
}

/**
 * Theme callback for the form table.
 */
function theme_socialfield_form_table(&$variables) {
  // Getting the userful values.
  $form = $variables['form'];
  $data = $form['rows'];
  $header = $form['#header'];
  $attributes = $form['#attributes'];

  // Traverse each row and each column in each row.
  $rows = array();
  foreach (element_children($data) as $row_index) {
    $row = array();
    foreach (element_children($data[$row_index]) as $col_index) {
      $element = $data[$row_index][$col_index];
      if (isset($element['#type']) && $element['#type'] == 'hidden') {
        continue;
      }
      $row[] = backdrop_render($data[$row_index][$col_index]);
    }

    $rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => $attributes
  ));

  backdrop_add_tabledrag($attributes['id'], 'order', 'sibling', 'services-order-weight');

  return $output;
}

/*******************************************************************************
 * Helper functions
 ******************************************************************************/

/**
 * Helper function, generates an 8 character random string.
 *
 * @see BackdropTestCase::randomName()
 */
function socialfield_random_string($length = 8) {
  $values = array_merge(range(65, 90), range(97, 122), range(48, 57));
  $max = count($values) - 1;
  $str = chr(mt_rand(97, 122));
  for ($i = 1; $i < $length; $i++) {
    $str .= chr($values[mt_rand(0, $max)]);
  }
  return $str;
}
