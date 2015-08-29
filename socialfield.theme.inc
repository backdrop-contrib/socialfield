<?php
/**
 * @file
 * Theme functions for Socialfield, placed here for improved developer experience.
 */

/**
 * Custom theme output for widget.
 */
function theme_socialfield_drag_components($vars) {
  $element = $vars['element'];
  backdrop_add_tabledrag('socialfield-table', 'order', 'sibling', 'item-row-weight');
  $services = config_get('socialfield.settings', 'services');

  $header = array(t($element['#title']), '', '', '');
  $rows = array();
  $index = 0;

  for ($i=0; $i<$element['#num_elements']; $i++) {
    while (!isset($element['element_' . $index])) {
      // There is no element with this index. Moving on to the next possible element.
      $index++;
    }
    $current_element = $element['element_' . $index];


    $rows[] = array(
      'data' => array(
        '<div class="social-links">' .
          '<span class="service-' . $current_element['#service'] . '">' .
            '<i class="icon ' . $services[$current_element['#service']]['icon'] . '">' . t($services[$current_element['#service']]['name']) . '</i>' .
          '</span>' .
        '</div>',
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

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'id' => 'socialfield-table'
    ),
  )) . backdrop_render($element['add_one_social']) . '<div class="description">' . backdrop_render($element['description']) . '</div>';
}

/**
 * Custom theme output for the formatter.
 */
function theme_socialfield_formatter($variables) {
  $label = array();
  $label_class = '';
  if (isset($variables['label']['mode']) && $variables['label']['mode'] != 'hidden') {
    $label = array(
      '#markup' => $variables['label']['label'],
      '#prefix' => '<div class="field-label">',
      '#suffix' => '</div>',
    );

    switch ($variables['label']['mode']) {
      case 'above':
        $label_class = 'field-label-above';
        break;
      case 'inline':
        $label_class = 'field-label-inline';
        break;
      case 'hidden':
        $label_class = 'field-label-hidden';
        break;
    }
  }

  $label = backdrop_render($label);

  $list = theme('item_list', array(
    'items' => $variables['items'],
    'attributes' => array('class' => array('field-items')),
  ));

  $field_classes = array(
    'field',
    'field-name-' . str_replace('_', '-', $variables['field']['field_name']),
    'field-type-' . str_replace('_', '-', $variables['field']['type']),
    $label_class,
    'social-links',
  );

  return '<div class="' . implode(' ', $field_classes) . '">' . $label . $list . '</div>';
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
