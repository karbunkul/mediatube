<ul>
<?php foreach ($items AS $item): ?>
  <li><?php print l($item['title'], 'mediatube/playlist/' . $item['alias']); ?></li>
  <?php endforeach;?>
</ul>