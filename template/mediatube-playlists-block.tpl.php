<ul>
<?php foreach ($items AS $item): ?>
  <li><i class="icon-home"></i>&nbsp;<?php print l($item['title'], 'mediatube/playlist/' . $item['alias']); ?></li>
  <?php endforeach;?>
</ul>